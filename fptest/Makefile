all: fptest

fptest: fptest.c
	gcc fptest.c -O2 -g -o fptest

clean:
	rm -f fptest

dist:
	rm -rf fptest-1/
	mkdir fptest-1
	cp Makefile fptest.c util.h fptest-1/
	tar -zcf fptest-1.tar.gz fptest-1/
	rm -rf fptest-1/

.PHONY: all clean
