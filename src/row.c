#include <stdbool.h>
#include <stdio.h>

#include "array.h"
#include "charutil.h"
#include "row.h"

void Row_print(Row *r) {
  printf("%08zx | ", r->offset);

  for (size_t c = 0; c < ROW_LEN; ++c) {
    printf("%02x", r->data[c]);

    if (c < ROW_LEN - 1) {
      printf(" ");
    }
  }

  printf(" | ");

  char display[3];
  for (size_t c = 0; c < ROW_LEN; ++c) {
    char_get_display(r->data[c], display);
    printf("%s", display);

    if (c < ROW_LEN - 1) {
      printf(" ");
    }
  }

  printf("\n");
}

bool Row_is_empty(Row *row) {
  return array_all_zeroes((char *)row->data, ROW_LEN);
}
