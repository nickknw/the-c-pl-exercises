CFLAGS=-Wall -Wextra -g
CC=clang

all: ex5-1 ex5-2 ex5-3 ex5-4 ex5-5 ex5-7 ex5-7_tests

ex5-1: ex5-1.c getch.o
ex5-2: ex5-2.c getch.o
ex5-3: ex5-3.c
ex5-4: ex5-4.c
ex5-5: ex5-5.c
ex5-7: ex5-7.o alloc.o bookgetline.o getch.o ex5-7_main.c
ex5-7_tests: ex5-7.o alloc.o bookgetline.o getch.o ex5-7_tests.c benchmark.o

clean:
	rm -f *.o
	rm -f ex5-[123456789]
	rm -rf *.dSYM
