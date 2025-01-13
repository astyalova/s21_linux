#ifndef PARSER_H
#define PARSER_H
typedef struct Arguments {
  int flag_e;
  int flag_i;
  int flag_v;
  int flag_c;
  int flag_l;
  int flag_n;
  int flag_h;
  int flag_s;
  int flag_f;
  int flag_o;
  char** patterns;
  char** files;
  int error;
  int count_files;
  int count_patterns;
} Arguments;
Arguments parser(int argc, char** argv);
#endif