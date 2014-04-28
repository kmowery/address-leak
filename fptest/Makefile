CC=gcc
LD=gcc
CFLAGS=-O2 -g
LDFLAGS=


all: fptest

fptest: main.o
	gcc -o $@ $^ $(LDFLAGS)

main.o: main.c Makefile
	gcc -o $@ -c $< $(CFLAGS)


clean:
	rm -f fptest main.o


.PHONY: all clean
