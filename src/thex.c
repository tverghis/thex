#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024
#define ROW_LEN 16
#define CHAR_SPACE 0x20
#define CHAR_LF 0x0A

bool is_printable_char(const unsigned char c) { return c >= '!' && c <= 126; }

void print_char_display(unsigned char c) {
  if (is_printable_char(c)) {
    printf("%2c", c);
  } else if (c == CHAR_SPACE) {
    printf("%2c", ' ');
  } else if (c == CHAR_LF) {
    printf("%2c", '_');
  } else if (c == 0) {
    printf("%2c", '.');
  } else {
    printf("%02X", c);
  }
}

void print_row(unsigned char *row) {
  for (size_t c = 0; c < ROW_LEN; ++c) {
    printf("%02X", row[c]);

    if (c < ROW_LEN - 1) {
      printf(" ");
    }
  }

  printf(" | ");

  for (size_t c = 0; c < ROW_LEN; ++c) {
    print_char_display(row[c]);

    if (c < ROW_LEN - 1) {
      printf(" ");
    }
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Error: expected name of file as first argument\n");
    return EXIT_FAILURE;
  }

  const char *filename = argv[1];

  FILE *file = fopen(filename, "rb");

  if (file == NULL) {
    perror("Failed to open file");
    return EXIT_FAILURE;
  }

  unsigned char buf[BUF_SIZE];

  unsigned char row[ROW_LEN];
  size_t col = 0;

  size_t n;
  while ((n = fread(&buf, sizeof *buf, BUF_SIZE, file)) > 0) {
    for (size_t i = 0; i < n; ++i) {
      row[col] = buf[i];
      col++;

      if (col == ROW_LEN) {
        col = 0;
        print_row(row);
        printf("\n");
      }
    }
  }

  if (ferror(file)) {
    perror("Failed to read from file");
    return EXIT_FAILURE;
  }

  fclose(file);

  return 0;
}
