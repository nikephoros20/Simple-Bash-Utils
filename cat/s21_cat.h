#ifndef S21_CAT_H
#define S21_CAT_H

#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool u;
  bool v;
} Options;

void set_options(char option, Options* opts);
void print_help();
void input_options(Options* opts, int argc, char* argv[]);
int print_file(char* name, Options* opts);
void print_symb(char c, int* prev, Options* opts, int* index,
                bool* eline_printed);

#endif  // S21_CAT_H