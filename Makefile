CC=gcc
CFLAGS=-std=c17 -Wall -Wextra -Wpedantic -g

thex: ./src/thex.c
	$(CC) $(CFLAGS) ./src/thex.c -o thex

clean:
	rm thex
