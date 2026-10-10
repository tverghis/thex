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

Printer Printer_new(void);

// A thin adapter around Printer_on_data so that it can be passed
// as the callback function in Reader_read_loop.
void Printer_read_cb(void *p, unsigned char *buf, size_t n);

void Printer_on_data(Printer *p, unsigned char *buf, size_t n);

#endif
