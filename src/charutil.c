#include <stdbool.h>
#include <stdio.h>

#include "charutil.h"

bool char_is_printable(unsigned char c)
{
    return c >= '!' && c <= '~';
}

void char_get_display(unsigned char c, char *out)
{
    if (char_is_printable(c))
    {
        sprintf(out, "%2c", c);
        return;
    }

    switch (c)
    {
    case CHAR_SPACE:
        sprintf(out, "%2c", ' ');
        break;
    case CHAR_LF:
        sprintf(out, "%2c", '_');
        break;
    case 0:
        sprintf(out, "%2c", '.');
        break;
    default:
        sprintf(out, "%02x", c);
    }
}
