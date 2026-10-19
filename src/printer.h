#ifndef THEX_PRINTER_H
#define THEX_PRINTER_H

#include <stdbool.h>
#include <stdlib.h>

#include "row.h"

struct printer
{
    size_t col;
    size_t offset;
    unsigned char row_data[ROW_LEN];
    bool last_row_empty;
    bool is_skipping_rows;
};

struct printer printer_new(void);

// A thin adapter around Printer_on_data so that it can be passed
// as the callback function in Reader_read_loop.
void printer_read_cb(void *p, unsigned char *buf, size_t n);

void printer_on_data(struct printer *p, unsigned char *buf, size_t n);

// Flushes any remaining accumulated bytes to the screen.
void printer_flush(struct printer *p);

#endif
