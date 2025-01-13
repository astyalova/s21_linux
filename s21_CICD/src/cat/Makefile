CC=gcc
CFLAGS= -Wall -Werror -Wextra


all: s21_cat
s21_cat: parser.c parser.h s21_cat.c
	$(CC)  $(CFLAGS) parser.c s21_cat.c -o s21_cat

clean:
	rm -rf *.o  s21_cat 

rebuild: clean all