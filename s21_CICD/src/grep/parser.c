#include "parser.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void parse_files(int argc, char** argv, Arguments* grep);
void parse_flags(int argc, char** argv, Arguments* grep);
void flag_f(Arguments* grep);

Arguments parser(int argc, char** argv) {
  Arguments grep;
  memset(&grep, 0, sizeof(Arguments));
  parse_flags(argc, argv, &grep);
  if (grep.flag_e && argc - optind < 1) {
    fprintf(stderr, "No file name found\n");
  }
  if (!grep.flag_e && !grep.flag_f && argc - optind < 2) {
    fprintf(stderr, "No pattern of file name found\n");
  }
  if (grep.flag_e || grep.flag_f) {
    parse_files(argc, argv, &grep);
  } else {
    grep.count_patterns++;
    grep.patterns = calloc(grep.count_patterns, sizeof(char*));
    if (grep.patterns == NULL) {
      fprintf(stderr, "Failed to allocate memory");
      exit(1);
    }
    grep.patterns[0] = strndup(
        argv[optind],
        strlen(argv[optind]));  // 1 аргумент указатель на строку которую
                                // копируем, второй - сколько байт из нее
                                // копировать, не учитывая \0
    if (grep.patterns[0] == NULL) {
      fprintf(stderr, "Failed to allocate memory");
      exit(1);
    }
    optind++;
    parse_files(argc, argv, &grep);
  }
  return grep;
}

void parse_files(int argc, char** argv, Arguments* grep) {
  grep->count_files = argc - optind;
  grep->files = calloc(grep->count_files, sizeof(char*));
  if (grep->files == NULL) {
    grep->error = 1;
    exit(1);
  }
  int cur_files = 0;
  while (optind < argc) {
    grep->files[cur_files++] = argv[optind++];
  }
}

void parse_flags(int argc, char** argv, Arguments* grep) {
  int cur_flag;
  int cur_pattern = 0;
  int long_index = 0;
  static struct option long_options[] = {
      {0, 0, 0, 0}};  // гетоптлонг принимает массив структур
  // нули нужны чтобы гетопт лонг понял когда заканчивается массив
  while ((cur_flag = getopt_long(argc, argv, "e:ivclnhsf:o", long_options,
                                 &long_index)) != -1) {
    switch (cur_flag) {
      case 'e':
        grep->flag_e = 1;
        grep->count_patterns++;
        grep->patterns =
            realloc(grep->patterns,
                    grep->count_patterns *
                        sizeof(char*));  // grep->patterns старый кусок памяти
        if (grep->patterns == NULL) {
          fprintf(stderr, "Failed to allocate memory");
          exit(1);
        }
        grep->patterns[cur_pattern] = strndup(optarg, strlen(optarg));
        if (grep->patterns[cur_pattern] == NULL) {
          fprintf(stderr, "Failed to allocate memory");
          exit(1);
        }
        cur_pattern++;
        break;
      case 'i':
        grep->flag_i = 1;
        break;
      case 'v':
        grep->flag_v = 1;
        break;
      case 'c':
        grep->flag_c = 1;
        break;
      case 'l':
        grep->flag_l = 1;
        break;
      case 'n':
        grep->flag_n = 1;
        break;
      case 'h':
        grep->flag_h = 1;
        break;
      case 's':
        grep->flag_s = 1;
        break;
      case 'f':
        flag_f(grep);
        grep->flag_f = 1;
        break;
      case 'o':
        grep->flag_o = 1;
        break;
      case '?':
        fprintf(stderr, "Wrong arguments\n");
        exit(1);
    }
  }
}
void flag_f(Arguments* grep) {
  FILE* file = fopen(optarg, "r");
  if (file == NULL) {
    fprintf(stderr, "Error, file doesn't open\n");
    exit(1);
  }
  char remembertext[1000];
  char* read_str;

  while ((read_str = fgets(remembertext, 1000, file)) != NULL) {
    // grep->kek == (*grep).kek
    int len = strlen(remembertext);
    grep->count_patterns++;
    grep->patterns =
        realloc(grep->patterns, grep->count_patterns * sizeof(char*));
    if (grep->patterns == NULL) {
      fprintf(stderr, "Failed to allocate memory");
      exit(1);
    }
    if (remembertext[len - 1] == '\n') {
      remembertext[len - 1] = 0;
    }
    grep->patterns[grep->count_patterns - 1] = strndup(remembertext, len);
    if (grep->patterns[grep->count_patterns - 1] == NULL) {
      fprintf(stderr, "Failed to allocate memory");
      exit(1);
    }
  }
}