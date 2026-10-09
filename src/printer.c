#include <stdio.h>

#include "array.h"
#include "printer.h"

Printer Printer_new(void) {
  Printer p = {.col = 0,
               .offset = 0,
               .row_data = {0},
               .last_row_empty = false,
               .is_skipping_rows = false};

  return p;
}

void Printer_on_data(Printer *p, unsigned char *buf, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    p->row_data[p->col] = buf[i];
    p->col++;

    if (p->col == ROW_LEN) {
      p->col = 0;
      Row thisRow = {.data = p->row_data, .offset = p->offset};

      if (array_all_zeroes((char *)p->row_data, ROW_LEN)) {
        if (p->last_row_empty) {
          if (!p->is_skipping_rows) {
            printf("*\n");
            p->is_skipping_rows = true;
          }
        } else {
          Row_print(&thisRow);
          p->is_skipping_rows = false;
        }
        p->last_row_empty = true;
      } else {
        Row_print(&thisRow);
        p->last_row_empty = false;
        p->is_skipping_rows = false;
      }

      p->offset += ROW_LEN;
    }
  }
}
