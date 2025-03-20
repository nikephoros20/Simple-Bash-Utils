#ifndef S21_GREP_H
#define S21_GREP_H

#define _GNU_SOURCE
#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patterns {
  char **arrays;
  regex_t *reg_arrays;
  size_t cur_size;
  size_t limit;
};

struct Specs {
  bool e;
  bool f;
  bool i;
  bool s;
  bool v;
  bool n;
  bool h;
  bool o;
  bool l;
  bool c;
  struct Patterns data;
  size_t file_count;
};

typedef struct Patterns Patterns;
typedef struct Specs Specs;

void *safe_realloc(void *ptr, size_t size);
void *safe_malloc(const size_t size);
void set_flags(Specs *const specs, const char opt);
void input_string(Patterns *const data, const char *const input_string);
void turn_to_regex(Specs *const specs);
void process_files(int file_count, char *const file_path[],
                   const Specs *const specs);
void free_memory(Patterns *const data);
void process_flags(FILE *file, const char *filename, const Specs *const specs);
void grep_n(FILE *file, const char *filename, const Specs *const specs);
bool is_match(const char *line, const Specs *const specs,
              regmatch_t *const match);
void grep_l(FILE *file, const char *filename, const Specs *const specs);
void grep_c(FILE *file, const Specs *const specs);
void input_from_file(Patterns *const data, char *const filename);
void grep_o(FILE *file, const Specs *const specs);

#endif  // S21_GREP_H