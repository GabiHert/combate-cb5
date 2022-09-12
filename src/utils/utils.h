#include <Arduino.h>
#include <string.h>
using namespace std;
#ifndef UTILS_H
#define UTILS_H

void loggerInfo(string event, string details, string message = " ");
void loggerError(string event, string details, string message = " ");
void loggerWarn(string event, string details, string message = " ");
char asciiCharToNumber(char c);
String stdStringToArduinoString(string str);
string arduinoStringToStdString(String str);
class Timer
{
private:
    unsigned long end;

public:
    Timer();
    void setTimer(unsigned int ms);
    bool status();
};

#endif // UTILS_H