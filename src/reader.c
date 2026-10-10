#include <stdio.h>

#include "reader.h"

int Reader_init(const char *filename, Reader *r) {
  FILE *file = fopen(filename, "rb");

  if (file == NULL) {
    return READER_EXIT_FAILURE;
  }

  r->file = file;

  return READER_EXIT_SUCCESS;
}

void Reader_close(Reader *self) { fclose(self->file); }

int Reader_read_loop(Reader *self, void *ctx, read_cb cb) {
  unsigned char buf[BUF_SIZE];
  size_t n;
  while ((n = fread(&buf, sizeof *buf, BUF_SIZE, self->file)) > 0) {
    (*cb)(ctx, buf, n);
  }

  if (ferror(self->file)) {
    return READER_EXIT_FAILURE;
  }

  return READER_EXIT_SUCCESS;
}
