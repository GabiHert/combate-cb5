#include <Arduino.h>

#ifndef LOGGER_H
#define LOGGER_H

void loggerInfo(String event, String details, String message = "");
void loggerError(String event, String details, String message = "");
void loggerWarn(String event, String details, String message = "");
#endif // LOGGER_H