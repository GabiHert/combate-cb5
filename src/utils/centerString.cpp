#include "utils/utils.h"

string centerString(string str, int length)
{
    int spaces = (length - str.length());

    if (spaces % 2)
        spaces--;

    while (spaces + str.length() > length)
        spaces--;

    string spacesStr;
    for (int i = 0; i < spaces / 2; i++)
        spacesStr += " ";

    return spacesStr + str + spacesStr;
}