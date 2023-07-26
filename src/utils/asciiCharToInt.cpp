#include "utils/utils.h"

char asciiCharToNumber(char c)
{
    if (c < 48)
    {
        return -1;
    }
    char number = c - 48;
    return number;
}