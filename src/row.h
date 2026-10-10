#ifndef THEX_ROW_H
#define THEX_ROW_H

#include <stdbool.h>
#include <stdlib.h>

#define ROW_LEN 16

typedef struct
{
    size_t offset;
    unsigned char *data;
    // number of bytes in data that are valid for this row
    size_t valid_bytes;
} row;

// Prints the rows offset and contents to screen.
void row_print(row *r);

// Returns true if the row data contains only zero-bytes.
bool row_is_empty(row *r);

#endif
