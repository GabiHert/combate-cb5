#include <Arduino.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
#ifndef UTILS_H
#define UTILS_H

// logger
void loggerInfo(string event, string details, string message = " ");
void loggerError(string event, string details, string message = " ");
void logger(string message);

// PARSER
char asciiCharToNumber(char c);
String stdStringToArduinoString(string str);
string arduinoStringToStdString(String str);
string centerString(string str, int length);
vector<string> splitStringBy(const string str, char separator);
char numberToProtocolNumber(char number);

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