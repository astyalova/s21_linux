#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int grep(Arguments arguments);
void flag_c(Arguments arguments, char **remembertext);
void print_line(char *remembertext, Arguments arguments, char *file_name,
                int line_number);

int main(int argc, char **argv) {
  Arguments arguments = parser(argc, argv);
  grep(arguments);
  for (int i = 0; i < arguments.count_patterns; i++) {
    free(arguments.patterns[i]);  // чищу то, что лежит в массиве
  }
  free(arguments.files);
  free(arguments.patterns);  // а тут указатель
}

int grep(Arguments arguments) {
  for (int i = 0; i < arguments.count_files; i++) {
    FILE *file = fopen(arguments.files[i], "r");
    if (file == NULL) {
      if (!arguments.flag_s) {
        fprintf(stderr, "Error, file doesn't open\n");
        continue;
      }
    }

    char remembertext[1000];
    regex_t regex;  // Структура
    int line_number = 0;
    int match_count = 0;
    int cflags = 0;

    if (arguments.flag_i) {
      cflags = cflags | REG_ICASE;  // Палка это побитовое или нужно
    }

    char *read_str;
    while ((read_str = fgets(remembertext, 1000, file)) != NULL) {
      line_number++;
      int matched = 0;

      if (remembertext[strlen(remembertext) - 1] == '\n') {
        remembertext[strlen(remembertext) - 1] = '\0';
      }

      for (int cur_pattern = 0; cur_pattern < arguments.count_patterns;
           cur_pattern++) {
        if (strlen(arguments.patterns[cur_pattern]) < 1) {
          matched = 1;
          continue;
        }
        int reti = regcomp(&regex, arguments.patterns[cur_pattern],
                           cflags);  // Переменная для проверки совпадений
        // 1) Принимает указатель на структуру regex, 2) Регулярное выражение
        // 3) Флаги, если есть. Если компиляция проходит успешно, regcomp
        // возвращает 0.
        if (reti) {
          if (!arguments.flag_s) {
            fprintf(stderr, "Could not compile regex\n");
            exit(1);
          }
        }
        reti = regexec(&regex, remembertext, 0, NULL, 0);
        // 1) Принимает скомпилированное выражение regex,
        // 2) Регулярное выражение в виде строки, в которой производится поиск,
        // 3) Флаги,
        // 4 и 5) Найденные совпадение.

        regfree(&regex);

        if (reti == 0) {
          matched = 1;
        }
      }
      if ((matched == 1 || arguments.flag_v) &&
          !(arguments.flag_v && matched == 1)) {
        // (1) && !(1)
        // 1 && 0
        // 0
        match_count++;

        if (!arguments.flag_c && !arguments.flag_l) {
          print_line(remembertext, arguments, arguments.files[i], line_number);
        }
      }
      if (match_count > 0 && arguments.flag_l) {
        break;
      }
    }
    if (arguments.flag_c) {
      if (arguments.flag_l) {
        match_count = match_count > 0;
      }
      if (arguments.count_files > 1 && !arguments.flag_h) {
        printf("%s:", arguments.files[i]);
      }
      printf("%d\n", match_count);
    }
    if (arguments.flag_l && match_count > 0) {
      printf("%s\n", arguments.files[i]);
    }

    if (ferror(file) != 0) {
      printf("fgets returned an error");
      exit(1);
    }

    if (fclose(file) != 0) {
      printf("Error closing file");
      exit(1);
    }
  }

  return 0;
}

void print_line(char *remembertext, Arguments arguments, char *file_name,
                int line_number) {
  if (arguments.count_files > 1 && !arguments.flag_h) {
    printf("%s:", file_name);
  }
  if (arguments.flag_n) {
    printf("%d:", line_number);
  }
  printf("%s\n", remembertext);
}