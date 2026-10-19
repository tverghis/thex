#ifndef THEX_DECODE_H
#define THEX_DECODE_H

#include <stddef.h>

enum decode_target
{
    U8BE,
    U16BE,
    U32BE,
    U64BE
};

/**
 * Interprets a given byte slice into the target type.
 * The output is stored at the location given by `out`.
 * The caller is responsible for ensuring that `out` is
 * sufficiently sized, as well as that `buf` contains sufficient
 * valid bytes to read (i.e., the number of bytes corresponding to `target`).
 */
int decode_slice(const unsigned char *buf, enum decode_target target,
                 void *out);

#endif
