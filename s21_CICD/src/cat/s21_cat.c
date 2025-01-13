#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
void print_flags(Arguments arguments, int line_number, int line_number_noempty,
                 int c);
void print_flags_with_text(Arguments arguments, int c);
int cat(Arguments arguments);

int main(int argc, char** argv) {
  Arguments arguments =
      parser(argc, argv);  // создаю структуру и возвращаю значение парсера
  cat(arguments);
  free(arguments.files);
}
// }//n
void print_flags(Arguments arguments, int line_number, int line_number_noempty,
                 int c) {
  if (arguments.b_f) {
    if (c == '\n') {
    } else {
      printf("%6d\t", line_number_noempty);
    }
  } else if (arguments.n_f) {
    printf("%6d\t", line_number);
  }
}
void print_flags_with_text(Arguments arguments, int c) {
  int print = 1;
  if (arguments.E_f) {
    if (c == '\n') {
      printf("$\n");
      print = 0;
    }
  }
  if (arguments.T_f) {
    if (c == '\t') {
      printf("^%c", c + 64);  // Заменяем символ табуляции
      print = 0;
    }
  }
  if (arguments.v_f) {
    if ((c >= 0) && (c < 32) && (c != 9) && (c != 10)) {
      printf("^%c", c + 64);
      print = 0;
    } else if (c > 127) {
      printf("M–^%c", c);
      print = 0;
    } else if (c == 127) {
      printf("^?");
      print = 0;
    }
  }
  if (print == 1) {
    printf("%c", c);
  }
}

int cat(Arguments arguments) {
  FILE* file;  // тип FILE, указатель на файл имеет тип FILE
  for (int i = 0; i < arguments.count_files; i++) {
    file = fopen(arguments.files[i],
                 "r");  // функция фопен открывает файл по указанному первому //
                        // аргументуи возвращает указатель на его начало // и
                        // читает(r)if (file == NULL) {
    if (file == NULL) {
      fprintf(stderr, "Error, file doesn't open\n");
      free(arguments.files);
      exit(1);
    }
    int c = fgetc(file);  // инициализация запомню текст
    int line_number = 1;
    int is_newline = 1;
    int is_empty = 0;
    int line_number_noempty = 1;
    while (c != EOF) {
      if (is_newline) {
        if (arguments.s_f && c == '\n' && is_empty) {
          c = fgetc(file);
          continue;
        }
        print_flags(arguments, line_number, line_number_noempty, c);
      }
      print_flags_with_text(arguments, c);
      if (c == '\n') {
        if (is_newline) {
          is_empty = 1;
        } else {
          line_number_noempty++;
        }
        is_newline = 1;
        line_number++;
      } else {
        is_empty = 0;
        is_newline = 0;
      }
      c = fgetc(file);
    }
    if (ferror(file) != 0) {  // проверяем вдруг fgets вернул ошибку
      fprintf(stderr, "fgets return error");
      exit(1);
    }
    if (fclose(file) != 0) {
      fprintf(stderr, "Error closing file");
      exit(1);
    }
  }

  return 0;
}