#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "printer.h"
#include "reader.h"

static int dispatch_cmd(const struct command *cmd);
static int do_print_cmd(const struct command *cmd);

int main(int argc, char *argv[])
{
    struct command cmd = parse_args(argc, argv);

    return dispatch_cmd(&cmd);
}

int dispatch_cmd(const struct command *cmd)
{
    if (cmd->type == INVALID)
    {
        return EXIT_FAILURE;
    }

    assert(cmd->filename != NULL);

    switch (cmd->type)
    {
    case PRINT:
    {
        if (do_print_cmd(cmd) == EXIT_FAILURE)
        {
            fprintf(stderr, "Failed to print file.\n");
            return EXIT_FAILURE;
        }
        break;
    }
    default:
    {
        fprintf(stderr, "Unimplemented command.\n");
        return EXIT_FAILURE;
    }
    }

    return EXIT_SUCCESS;
}

int do_print_cmd(const struct command *cmd)
{
    struct reader r;
    if (reader_init(cmd->filename, &r) == READER_EXIT_FAILURE)
    {
        perror("Failed to initialize reader");
        return EXIT_FAILURE;
    }

    struct printer p = printer_new();
    if (reader_read_loop(&r, &p, &printer_read_cb) == READER_EXIT_FAILURE)
    {
        perror("Failed to read from file");
        return EXIT_FAILURE;
    }

    printer_flush(&p);

    reader_close(&r);

    return EXIT_SUCCESS;
}
