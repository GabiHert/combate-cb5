#include "utils/utils.h"

String stdStringToArduinoString(string str)
{
    String arduinoStr;

    for (int c = 0; c < str.length(); c++)
    {
        arduinoStr += str[c];
    }
    return arduinoStr;
}

string arduinoStringToStdString(String str)
{
    string stdStr;

    for (int c = 0; c < str.length(); c++)
    {
        stdStr += str[c];
    }
    return stdStr;
}