#ifndef THEX_PRINTER_H
#define THEX_PRINTER_H

#include <stdbool.h>
#include <stdlib.h>

#include "row.h"

typedef struct {
  size_t col;
  size_t offset;
  unsigned char row_data[ROW_LEN];
  bool last_row_empty;
  bool is_skipping_rows;
} Printer;

void Printer_on_data(Printer *p, unsigned char *buf, size_t n);

#endif
