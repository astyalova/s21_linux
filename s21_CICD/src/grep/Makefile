CC=gcc
CFLAGS= -Wall -Werror -Wextra


all: s21_grep
s21_grep: parser.c parser.h s21_grep.c
	$(CC)  $(CFLAGS) parser.c s21_grep.c -o s21_grep

clean:
	rm -rf *.o  s21_grep 

rebuild: clean all