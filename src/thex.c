#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "row.h"

#define BUF_SIZE 1024

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
  size_t offset = 0;
  size_t col = 0;

  bool last_row_all_zeroes = false;
  bool skipping_rows = false;

  size_t n;
  while ((n = fread(&buf, sizeof *buf, BUF_SIZE, file)) > 0) {
    for (size_t i = 0; i < n; ++i) {
      row[col] = buf[i];
      col++;

      if (col == ROW_LEN) {
        col = 0;
        Row thisRow = {.data = row, .offset = offset};

        if (array_all_zeroes((char *)row, ROW_LEN)) {
          if (last_row_all_zeroes) {
            if (!skipping_rows) {
              printf("*\n");
              skipping_rows = true;
            }
          } else {
            Row_print(&thisRow);
            skipping_rows = false;
          }
          last_row_all_zeroes = true;
        } else {
          Row_print(&thisRow);
          last_row_all_zeroes = false;
          skipping_rows = false;
        }

        offset += ROW_LEN;
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
