#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arguments parser(int argc, char **argv) {
  Arguments parser_arg;
  parser_arg.b_f = 0;
  parser_arg.n_f = 0;
  parser_arg.s_f = 0;
  parser_arg.E_f = 0;
  parser_arg.v_f = 0;
  parser_arg.T_f = 0;
  int long_flag;
  int i = 1;
  parser_arg.count_files = 0;
  while (i < argc) {
    if (argv[i][0] != '-') {
      parser_arg.count_files++;
    }
    i++;
  }
  parser_arg.files =
      calloc(parser_arg.count_files,
             sizeof(char *));  // возвращает указатель на первую ячейку памяти,
                               // в случае провала возращает указатель на нул.
  if (parser_arg.files == NULL) {
    fprintf(stderr, "Failed to allocate memory");
    exit(1);
  }

  i = 1;
  int cur_files = 0;
  while (i < argc) {
    if (strcmp(argv[i], "--number-nonblank") == 0) {
      parser_arg.b_f = 1;
      long_flag = 1;
    } else if (strcmp(argv[i], "--number") == 0) {
      parser_arg.n_f = 1;
      long_flag = 1;
    } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
      parser_arg.s_f = 1;
      long_flag = 1;
    }
    int j = 1;
    while (argv[i][j] != '\0') {
      if (argv[i][0] == '-' && argv[i][j] == 'b') {
        parser_arg.b_f = 1;
      } else if (argv[i][0] == '-' && argv[i][j] == 'e') {
        parser_arg.E_f = 1;
        parser_arg.v_f = 1;
      } else if (argv[i][0] == '-' && argv[i][j] == 'n') {
        parser_arg.n_f = 1;
      } else if (argv[i][0] == '-' && argv[i][j] == 's') {
        parser_arg.s_f = 1;
      } else if (argv[i][0] == '-' && argv[i][j] == 't') {
        parser_arg.T_f = 1;
        parser_arg.v_f = 1;
      } else if (argv[i][0] == '-' && argv[i][j] == 'E') {
        parser_arg.E_f = 1;
      } else if (argv[i][0] == '-' && argv[i][j] == 'v') {
        parser_arg.v_f = 1;
      } else if (argv[i][0] == '-' && argv[i][j] == 'T') {
        parser_arg.T_f = 1;
      } else if (argv[i][0] == '-' && long_flag != 1) {
        fprintf(stderr, "Wrong input");
        exit(1);
      }
      j++;
    }
    if (argv[i][0] != '-') {
      parser_arg.files[cur_files] = argv[i];
      cur_files++;
    }

    i++;
  }
  return parser_arg;
}
