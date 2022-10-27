#include "utils/utils.h"

String stdStringToArduinoString(string str)
{
    String arduinoStr = "";

    for (int c = 0; c < str.length(); c++)
    {
        arduinoStr += str.at(c);
    }
    return arduinoStr;
}

string arduinoStringToStdString(String str)
{

    return string(str.c_str());
}