#include <assert.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "charutil.h"
#include "row.h"

void print_raw(row *r);
void print_display(row *r);

void row_print(row *r)
{
    assert(r->valid_bytes <= ROW_LEN);

    printf("%08zx", r->offset);
    printf(" | ");
    print_raw(r);
    printf(" | ");
    print_display(r);
    printf("\n");
}

void print_raw(row *r)
{
    for (size_t c = 0; c < ROW_LEN; ++c)
    {
        if (c < r->valid_bytes)
        {
            printf("%02x", r->data[c]);
        }
        else
        {
            printf("%2c", ' ');
        }

        if (c < ROW_LEN)
        {
            printf(" ");
        }
    }
}

void print_display(row *r)
{
    char display[3];
    for (size_t c = 0; c < ROW_LEN; ++c)
    {
        if (c < r->valid_bytes)
        {
            char_get_display(r->data[c], display);
            printf("%s", display);
        }
        else
        {
            printf("%2c", ' ');
        }

        if (c < ROW_LEN)
        {
            printf(" ");
        }
    }
}
