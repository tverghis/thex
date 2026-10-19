#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "strings.h"

#define CMD_PRINT "print"
#define CMD_DECODE "decode"

struct command parse_args(int argc, char *const argv[])
{
    struct command ret = {.type = INVALID};

    if (argc < 3)
    {
        fprintf(stderr,
                "Error: invalid number of arguments (expected at least 2, "
                "found %d).\n",
                argc - 1);
        return ret;
    }

    ret.filename = argv[2];

    const char *cmd = argv[1];

    if (thex_string_eq(cmd, CMD_PRINT))
    {
        ret.type = PRINT;
    }
    else if (thex_string_eq(cmd, CMD_DECODE))
    {
        ret.type = DECODE;
    }
    else
    {
        fprintf(stderr, "Error: invalid command %s.\n", argv[1]);
        return ret;
    }

    return ret;
}
