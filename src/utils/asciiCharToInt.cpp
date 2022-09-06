#include "utils/utils.h"

char asciiCharToNumber(char c)
{
    loggerInfo("asciiCharToNumber", "Process started", "received char: " + String(c));
    int number = c - 48;
    loggerInfo("asciiCharToNumber", "Process finished", " number: " + String(number));
    return number;
}