#include "decode.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DECODE_UINT(TGT_TYP, WD_BYTES, IN_PTR, OUT_PTR)                        \
    do                                                                         \
    {                                                                          \
        TGT_TYP acc = 0;                                                       \
        for (size_t i = 0; i < (WD_BYTES); ++i)                                \
        {                                                                      \
            acc = acc << 8;                                                    \
            acc |= (IN_PTR)[i];                                                \
        }                                                                      \
        *((TGT_TYP *)(OUT_PTR)) = acc;                                         \
    } while (false)

int decode_slice(const unsigned char *buf, enum decode_target target, void *out)
{
    switch (target)
    {
    case U8BE:
    {
        DECODE_UINT(uint8_t, 1, buf, out);
        break;
    }
    case U16BE:
    {
        DECODE_UINT(uint16_t, 2, buf, out);
        break;
    }
    case U32BE:
    {
        DECODE_UINT(uint32_t, 4, buf, out);
        break;
    }
    case U64BE:
    {
        DECODE_UINT(uint64_t, 8, buf, out);
        break;
    }
    default:
    {
        fprintf(stderr, "Invalid decode target %d.\n", target);
        return EXIT_FAILURE;
    }
    }

    return EXIT_SUCCESS;
}
