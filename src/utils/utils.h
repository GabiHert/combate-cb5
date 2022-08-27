#include <Arduino.h>

#ifndef UTILS_H
#define UTILS_H

void loggerInfo(String event, String details, String message = "");
void loggerError(String event, String details, String message = "");
void loggerWarn(String event, String details, String message = "");

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