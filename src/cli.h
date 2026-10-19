#ifndef THEX_CLI_H
#define THEX_CLI_H

enum command_type
{
    PRINT,
    DECODE,
    INVALID,
};

struct command
{
    enum command_type type;
    const char *filename;
};

struct command parse_args(int argc, char *const argv[]);

#endif
