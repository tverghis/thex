#ifndef THEX_ROW_H
#define THEX_ROW_H

#include <stdbool.h>
#include <stdlib.h>

#define ROW_LEN 16

typedef struct {
  size_t offset;
  unsigned char *data;
} Row;

// Prints the rows offset and contents to screen.
void Row_print(Row *row);

// Returns true if the row contains no data.
bool Row_is_empty(Row *row);

#endif
