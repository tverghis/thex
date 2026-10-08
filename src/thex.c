#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024
#define ROW_LEN 8

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
  while ((n = fread(&buf, sizeof *buf, BUF_SIZE, file)) > 0) {
    for (int i = 0; i < n; ++i) {
      printf("%02X", buf[i]);
      if ((i + 1) % ROW_LEN == 0) {
        printf("\n");
      } else {
        printf(" ");
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
