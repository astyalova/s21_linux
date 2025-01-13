#ifndef PARSER_H
#define PARSER_H
typedef struct Arguments {
  int b_f;
  int n_f;
  int s_f;
  int E_f;
  int v_f;
  int T_f;
  char** files;
  int count_files;
} Arguments;
Arguments parser(int argc, char** argv);
#endif