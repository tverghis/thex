#include <stdio.h>

#include "printer.h"
#include "row.h"

struct printer printer_new(void)
{
    struct printer p = {
        .col = 0,
        .offset = 0,
        .row_data = {0},
        .last_row_empty = false,
        .is_skipping_rows = false,
    };

    return p;
}

void printer_read_cb(void *p, unsigned char *buf, size_t n)
{
    printer_on_data((struct printer *)p, buf, n);
}

void printer_on_data(struct printer *p, unsigned char *buf, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        p->row_data[p->col] = buf[i];
        p->col++;

        if (p->col == ROW_LEN)
        {
            struct row thisRow = {
                .data = p->row_data,
                .offset = p->offset,
                .valid_bytes = p->col,
            };
            p->col = 0;

            if (row_is_empty(&thisRow))
            {
                if (p->last_row_empty)
                {
                    if (!p->is_skipping_rows)
                    {
                        printf("*\n");
                        p->is_skipping_rows = true;
                    }
                }
                else
                {
                    row_print(&thisRow);
                    p->is_skipping_rows = false;
                }
                p->last_row_empty = true;
            }
            else
            {
                row_print(&thisRow);
                p->last_row_empty = false;
                p->is_skipping_rows = false;
            }

            p->offset += ROW_LEN;
        }
    }
}

void printer_flush(struct printer *p)
{
    if (p->col == 0)
    {
        return;
    }

    struct row thisRow = {
        .data = p->row_data,
        .offset = p->offset,
        .valid_bytes = p->col,
    };
    row_print(&thisRow);
}
