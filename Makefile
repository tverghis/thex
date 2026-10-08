
thex: ./src/thex.c
	gcc -std=c17 -Wall -Wextra -Wpedantic ./src/thex.c -o thex

clean:
	rm thex
