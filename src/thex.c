#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "printer.h"
#include "reader.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Error: expected name of file as first argument\n");
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];

    reader r;
    if (reader_init(filename, &r) == READER_EXIT_FAILURE)
    {
        perror("Failed to initialize reader");
        return EXIT_FAILURE;
    }

    printer p = printer_new();
    if (reader_read_loop(&r, &p, &printer_read_cb) == READER_EXIT_FAILURE)
    {
        perror("Failed to read from file");
        return EXIT_FAILURE;
    }

    printer_flush(&p);

    reader_close(&r);

    return 0;
}
