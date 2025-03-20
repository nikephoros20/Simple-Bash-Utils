#include "s21_grep.h"

const char ALL_FLAGS[] = "e:f:isvnholc";

int main(int argc, char *argv[]) {
  Specs specs = {0};
  specs.data.cur_size = 0;
  specs.data.limit = 128;
  specs.data.arrays = safe_malloc(sizeof(char *) * specs.data.limit);

  char curr_opt = getopt(argc, argv, ALL_FLAGS);
  while (curr_opt != -1) {
    set_flags(&specs, curr_opt);
    curr_opt = getopt(argc, argv, ALL_FLAGS);
  }
  if (!specs.e && !specs.f) {
    input_string(&specs.data, argv[optind++]);
  }
  turn_to_regex(&specs);
  specs.file_count = argc - optind;
  process_files(argc - optind, argv + optind, &specs);
  free_memory(&specs.data);
  return 0;
}

void input_string(Patterns *const data, const char *const input_string) {
  size_t str_len = strlen(input_string);
  char *str_copy = malloc(str_len + 1);
  strcpy(str_copy, input_string);
  char *token = strtok(str_copy, "\n");
  while (token != NULL) {
    if (data->cur_size == data->limit) {
      data->limit += 128;
      data->arrays = safe_realloc(data->arrays, data->limit * sizeof(char *));
    }
    size_t token_len = strlen(token);
    data->arrays[data->cur_size] =
        safe_malloc(sizeof(char) * token_len + sizeof(char));
    strcpy(data->arrays[data->cur_size++], token);
    token = strtok(NULL, "\n");
  }
  free(str_copy);
}

void process_flags(FILE *file, const char *filename, const Specs *const specs) {
  if (specs->l) {
    grep_l(file, filename, specs);
  } else if (specs->c) {
    grep_c(file, specs);
  } else if (specs->o) {
    grep_o(file, specs);
  } else {
    grep_n(file, filename, specs);
  }
}

void process_files(int file_count, char *const file_path[],
                   const Specs *const specs) {
  for (FILE *curr_file = NULL; file_count--; ++file_path) {
    curr_file = fopen(*file_path, "r");
    if (curr_file != NULL) {
      process_flags(curr_file, *file_path, specs);
      fclose(curr_file);
    } else if (!specs->s) {
      fprintf(stderr, "%s: No such file or directory\n", *file_path);
    }
  }
}

void grep_o(FILE *file, const Specs *const specs) {
  int line_count = 0;
  char *line = NULL;
  size_t len = 0;
  regmatch_t match = {0};
  while (getline(&line, &len, file) != -1) {
    ++line_count;
    if (is_match(line, specs, &match)) {
      const char *start = line;
      while (is_match(start, specs, &match)) {
        for (int i = match.rm_so; i < match.rm_eo; i++) {
          putchar(start[i]);
        }
        putchar('\n');
        start += match.rm_eo;
      }
    }
  }
  free(line);
}

void grep_c(FILE *file, const Specs *const specs) {
  char *line = NULL;
  size_t len = 0;
  int match_count = 0;
  while ((getline(&line, &len, file)) != EOF) {
    if (is_match(line, specs, NULL)) {
      ++match_count;
    }
  }
  fprintf(stdout, "%d\n", match_count);
  free(line);
}

void grep_l(FILE *file, const char *filename, const Specs *const specs) {
  char *line = NULL;
  size_t len = 0;
  while ((getline(&line, &len, file)) != EOF) {
    if (is_match(line, specs, NULL)) {
      fprintf(stdout, "%s\n", filename);
      break;
    }
  }
  free(line);
}

void grep_n(FILE *file, const char *filename, const Specs *const specs) {
  char *line = NULL;
  size_t len = 0;
  int line_count = 0;
  while (getline(&line, &len, file) != EOF) {
    ++line_count;
    if (is_match(line, specs, NULL)) {
      if (specs->file_count > 1 && !specs->h) {
        fprintf(stdout, "%s:", filename);
      }
      if (specs->n) {
        fprintf(stdout, "%d:", line_count);
      }
      fprintf(stdout, "%s", line);
    }
  }
  free(line);
}

bool is_match(const char *line, const Specs *const specs,
              regmatch_t *const match) {
  const Patterns *const data = &specs->data;
  bool result = false;
  size_t nmatch = 0;
  if (match != NULL) {
    nmatch = 1;
  }
  for (size_t i = 0; i < data->cur_size; ++i) {
    if (regexec(&data->reg_arrays[i], line, nmatch, match, 0) == 0) {
      result = true;
    }
  }
  if (specs->v) {
    result = !result;
    if (specs->o) {
      result = false;
    }
  }
  return result;
}

void turn_to_regex(Specs *const specs) {
  Patterns *data = &specs->data;
  data->reg_arrays = safe_malloc(sizeof(regex_t) * data->cur_size);
  int reg_icase = 0;
  if (specs->i) {
    reg_icase = REG_ICASE;
  }
  for (size_t i = 0; i < data->cur_size; ++i) {
    regcomp(&data->reg_arrays[i], data->arrays[i], reg_icase);
  }
}

void set_flags(Specs *const specs, const char opt) {
  switch (opt) {
    case 'e':
      specs->e = true;
      input_string(&specs->data, optarg);
      break;
    case 'f':
      specs->f = true;
      input_from_file(&specs->data, optarg);
      break;
    case 'i':
      specs->i = true;
      break;
    case 's':
      specs->s = true;
      break;
    case 'v':
      specs->v = true;
      break;
    case 'n':
      specs->n = true;
      break;
    case 'h':
      specs->h = true;
      break;
    case 'o':
      specs->o = true;
      break;
    case 'l':
      specs->l = true;
      break;
    case 'c':
      specs->c = true;
      break;
    case 0:
      fprintf(stdout, "Usage: grep [OPTION]... Patterns [FILE]...\n");
      exit(EXIT_FAILURE);
      break;
    case '?':
    default:
      fprintf(stderr, "Try 'grep --help' for more information.\n");
      exit(EXIT_FAILURE);
  }
}

void *safe_malloc(const size_t size) {
  void *pointer = malloc(size);
  if (pointer == NULL) {
    fprintf(stderr, "Error: Unable to allocate for %zu.\n", size);
    exit(EXIT_FAILURE);
  }
  return pointer;
}

void free_memory(Patterns *const data) {
  for (size_t i = 0; i < data->cur_size; ++i) {
    free(data->arrays[i]);
    regfree(&data->reg_arrays[i]);
  }
  free(data->arrays);
  free(data->reg_arrays);
}

void input_from_file(Patterns *const data, char *const filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "%s: No such file or directory\n", filename);
    exit(EXIT_FAILURE);
  }
  char *buffer = safe_malloc(sizeof(char) * 128);
  size_t size = 0;
  size_t max_size = 128;
  char symbol = fgetc(file);
  while (!feof(file)) {
    buffer[size++] = symbol;
    symbol = fgetc(file);
    if (size == max_size) {
      max_size *= 2;
      buffer = safe_realloc(buffer, max_size * sizeof(char));
    }
  }
  buffer[size] = '\0';
  input_string(data, buffer);
  free(buffer);
  fclose(file);
}

void *safe_realloc(void *ptr, size_t size) {
  void *r_pointer = realloc(ptr, size);
  if (r_pointer == NULL) {
    fprintf(stderr, "Error: Unable to allocate for %zu.\n", size);
    exit(EXIT_FAILURE);
  }
  return r_pointer;
}
