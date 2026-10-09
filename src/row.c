#include <stdbool.h>
#include <stdio.h>

#include "charutil.h"
#include "row.h"

void print_raw(Row *r);
void print_display(Row *r);

void Row_print(Row *r) {
  printf("%08zx", r->offset);
  printf(" | ");
  print_raw(r);
  printf(" | ");
  print_display(r);
  printf("\n");
}

void print_raw(Row *r) {
  for (size_t c = 0; c < ROW_LEN; ++c) {
    printf("%02x", r->data[c]);

    if (c < ROW_LEN - 1) {
      printf(" ");
    }
  }
}

void print_display(Row *r) {
  char display[3];
  for (size_t c = 0; c < ROW_LEN; ++c) {
    char_get_display(r->data[c], display);
    printf("%s", display);

    if (c < ROW_LEN - 1) {
      printf(" ");
    }
  }
}
