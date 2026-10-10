#include "array.h"

bool array_all_zeroes(char *arr, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        if (arr[i] != 0)
            return false;
    }

    return true;
}
