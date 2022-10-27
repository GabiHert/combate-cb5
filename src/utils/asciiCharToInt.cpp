#include "utils/utils.h"

char asciiCharToNumber(char c)
{
    loggerInfo("asciiCharToNumber", "Process started", "received char: " + to_string(c));
    if (c < 48)
    {
        loggerWarn("asciiCharToNumber", "Process warn", "char cant be parsed");
        return -1;
    }
    int number = c - 48;
    loggerInfo("asciiCharToNumber", "Process finished", " number: " + to_string(number));
    return number;
}