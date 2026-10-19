#ifndef THEX_READER_H
#define THEX_READER_H

#include <stdio.h>

#define READER_EXIT_SUCCESS 0
#define READER_EXIT_FAILURE 1
#define BUF_SIZE 1024

struct reader
{
    FILE *file;
};

// Type for the callback function that is invoked when a chunk is read
typedef void (*read_cb)(void *ctx, unsigned char *buf, size_t n);

int reader_init(const char *filename, struct reader *r);
void reader_close(struct reader *self);

// Read the file in chunks, and call cb whenever a chunk has been fully read.
// ctx is passed as the first argument to cb.
int reader_read_loop(struct reader *self, void *ctx, read_cb cb);

#endif
