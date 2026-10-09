#ifndef THEX_CHARUTIL_H
#define THEX_CHARUTIL_H

#include <stdbool.h>

#define CHAR_SPACE 0x20
#define CHAR_LF 0x0A

// Returns true if the char is an ASCII value that can be printed to screen.
bool char_is_printable(unsigned char c);

// Puts the display representation of the character c in the output string out.
// out is expected to be a string of length 3. The string will be
// null-terminated.
void char_get_display(unsigned char c, char *out);

#endif
