#include "s21_cat.h"

const char ALL_FLAGS[] = "AbeEnstTuvh";

int main(int argc, char* argv[]) {
  Options opts = {0};
  input_options(&opts, argc, argv);
  (argv[2]) ? print_file(argv[2], &opts) : print_file(argv[1], &opts);
  return 0;
}

void print_symb(char c, int* prev, Options* opts, int* index,
                bool* eline_printed) {
  bool need_s = 0;
  if (opts->s == true && *prev == '\n' && c == '\n' && *eline_printed == 1)
    need_s = 1;
  if (need_s == 0) {
    if (*prev == '\n' && c == '\n')
      *eline_printed = 1;
    else
      *eline_printed = 0;
    if (((opts->n == true && opts->b != true) ||
         (opts->b == true && c != '\n')) &&
        *prev == '\n') {
      *index += 1;
      printf("%6d\t", *index);
    }
    if (opts->e == true && c == '\n') printf("$");
    if (opts->t == true && c == '\t') {
      printf("^");
      c = '\t' + 64;
    }
    if (opts->v == true && iscntrl(c) && c != '\n' && c != '\t') {
      printf("^");
      if (c != 127) {
        c = c + 64;
      } else {
        c = c - 64;
      }
    }
    if (opts->v == true && iscntrl(c) == 0 && isprint(c) == 0 && c != '\n' &&
        c != '\t') {
      c = (signed char)c + 128;
      printf("M");
      printf("-");
      if (isprint(c) == 0) {
        printf("^");
        if (c != 127) {
          c = c + 64;
        } else {
          c = c - 64;
        }
      }
    }
    fputc(c, stdout);
  }
  *prev = c;
}

int print_file(char* name, Options* opts) {
  // printf("Variable name - %s", name);
  FILE* f = fopen(name, "rt");
  if (f != NULL) {
    int index = 0;
    bool eline_printed = false;
    int c = fgetc(f), prev = '\n';
    while (c != EOF) {
      print_symb(c, &prev, opts, &index, &eline_printed);
      c = fgetc(f);
    }
    fclose(f);
  } else {
    printf("Error\n");
  }
  return 1;
}

void input_options(Options* opts, int argc, char* argv[]) {
  char current_option = getopt(argc, argv, ALL_FLAGS);
  while (current_option != -1) {
    set_options(current_option, opts);
    current_option = getopt(argc, argv, ALL_FLAGS);
  }
}

void set_options(char option, Options* opts) {
  switch (option) {
    case 'A':
      opts->v = true;
      opts->e = true;
      opts->t = true;
      break;
    case 'b':
      opts->b = true;
      break;
    case 'e':
      opts->v = true;
      opts->e = true;
      break;
    case 'E':
      opts->e = true;
      break;
    case 'n':
      opts->n = true;
      break;
    case 's':
      opts->s = true;
      break;
    case 't':
      opts->v = true;
      opts->t = true;
      break;
    case 'T':
      opts->t = true;
      break;
    case 'v':
      opts->v = true;
      break;
    case '?':
      printf("Try '--help' for more information.\n");
      break;
    case 0:
      printf("Usage: cat [OPTION]... [FILE]...\n");
      break;
  }
}