#include <Arduino.h>
#include <string.h>
using namespace std;
#ifndef UTILS_H
#define UTILS_H

// LOGGER
void loggerInfo(string event, string details, string message = " ");
void loggerError(string event, string details, string message = " ");
void loggerWarn(string event, string details, string message = " ");

// PARSER
char asciiCharToNumber(char c);
String stdStringToArduinoString(string str);
string arduinoStringToStdString(String str);

// TIMER
class Timer
{
private:
    unsigned long end;

public:
    Timer();
    void setTimer(unsigned long ms);
    void wait();
    bool timedOut();
};

#endif // UTILS_H