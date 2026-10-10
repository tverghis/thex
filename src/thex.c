#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "printer.h"
#include "reader.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Error: expected name of file as first argument\n");
    return EXIT_FAILURE;
  }

  const char *filename = argv[1];

  Reader reader;
  if (Reader_init(filename, &reader) == READER_EXIT_FAILURE) {
    perror("Failed to initialize reader");
    return EXIT_FAILURE;
  }

  Printer p = Printer_new();
  if (Reader_read_loop(&reader, &p, &Printer_read_cb) == READER_EXIT_FAILURE) {
    perror("Failed to read from file");
    return EXIT_FAILURE;
  }

  Reader_close(&reader);

  return 0;
}
