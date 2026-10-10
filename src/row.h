#ifndef THEX_ROW_H
#define THEX_ROW_H

#include <stdbool.h>
#include <stdlib.h>

#define ROW_LEN 16

typedef struct
{
    size_t offset;
    unsigned char *data;
    size_t valid_bytes;
} row;

// Prints the rows offset and contents to screen.
void row_print(row *row);

#endif
