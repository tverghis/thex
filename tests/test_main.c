#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/decode.h"

#define TEST_PASS true
#define TEST_FAIL false

#define TEST_DECODE_UINT(TARGET, TGT_TYP, EXPECTED, ...)                       \
    bool test_decode_##TARGET(void)                                            \
    {                                                                          \
        TGT_TYP out = 0;                                                       \
        const unsigned char buf[] = {__VA_ARGS__};                             \
        if (decode_slice(buf, TARGET, &out) != EXIT_SUCCESS)                   \
        {                                                                      \
            fprintf(stderr,                                                    \
                    "test_decode_" #TARGET ": decode_slice did not exit "      \
                    "with success.\n");                                        \
            return TEST_FAIL;                                                  \
        }                                                                      \
        if (out != (EXPECTED))                                                 \
        {                                                                      \
            uintmax_t out_ = out;                                              \
            uintmax_t expected_ = EXPECTED;                                    \
            fprintf(stderr,                                                    \
                    "test_decode_" #TARGET ": expected 0x%" PRIXMAX            \
                    ", got 0x%" PRIXMAX "\n",                                  \
                    expected_, out_);                                          \
            return TEST_FAIL;                                                  \
        }                                                                      \
        return TEST_PASS;                                                      \
    }

TEST_DECODE_UINT(U8BE, uint8_t, 0xAB, 0xAB)
TEST_DECODE_UINT(U16BE, uint16_t, 0xABCD, 0xAB, 0xCD)
TEST_DECODE_UINT(U32BE, uint32_t, 0x89ABCDEF, 0x89, 0xAB, 0xCD, 0xEF)
TEST_DECODE_UINT(U64BE, uint64_t, 0x89ABCDEFABCDFF00, 0x89, 0xAB, 0xCD, 0xEF,
                 0xAB, 0xCD, 0xFF, 0x00)

int main(void)
{
    bool result = test_decode_U8BE() && test_decode_U16BE() &&
                  test_decode_U32BE() && test_decode_U64BE();

    if (result)
    {
        printf("All tests passed!\n");
        return EXIT_SUCCESS;
    }
    else
    {
        printf("Some tests failed.\n");
        return EXIT_FAILURE;
    }
}
