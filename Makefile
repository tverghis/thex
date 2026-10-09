CC=gcc
CFLAGS=-std=c17 -Wall -Wextra -Wpedantic
OUTDIR=./out

program: thex.o array.o
	$(CC) $(OUTDIR)/thex.o $(OUTDIR)/array.o -o $(OUTDIR)/thex

thex.o: out-dir array.o ./src/thex.c ./src/array.h
	$(CC) $(CFLAGS) -c ./src/thex.c -o $(OUTDIR)/thex.o

array.o: out-dir ./src/array.c ./src/array.h
	$(CC) $(CFLAGS) -c ./src/array.c -o $(OUTDIR)/array.o

out-dir:
	mkdir -p $(OUTDIR)

clean:
	rm -r $(OUTDIR)

.PHONY: clean
