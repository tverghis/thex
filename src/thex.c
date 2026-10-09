#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "printer.h"

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
  size_t n;
  Printer p = Printer_new();
  while ((n = fread(&buf, sizeof *buf, BUF_SIZE, file)) > 0) {
    Printer_on_data(&p, buf, n);
  }

  if (ferror(file)) {
    perror("Failed to read from file");
    return EXIT_FAILURE;
  }

  fclose(file);

  return 0;
}
