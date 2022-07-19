#include <Arduino.h>
#include "utils/utils.h"

void loggerInfo(String event, String details, String message)
{

    Serial.print("INFO - :: - ");

    Serial.print("  event: ");
    Serial.print(event);
    Serial.print(" | ");
    Serial.print("  details: ");
    Serial.print(details);
    Serial.print(" | ");

    Serial.print(" message: ");
    Serial.print(message);
    Serial.print(" | ");

    Serial.println();
};

void loggerError(String event, String details, String error)
{

    Serial.print("ERROR - :: - ");
    Serial.print(" | ");

    Serial.print("  event: ");
    Serial.print(event);
    Serial.print(" | ");

    Serial.print("  details: ");
    Serial.print(details);
    Serial.print(" | ");

    Serial.print("  error: ");
    Serial.print(error);
    Serial.print(" | ");

    Serial.println();
};

void loggerwarn(String event, String details, String warn)
{

    Serial.print("WARN - :: - ");

    Serial.print("  event: ");
    Serial.print(event);
    Serial.print(" | ");

    Serial.print("  details: ");
    Serial.print(details);
    Serial.print(" | ");

    Serial.print("  warn: ");
    Serial.print(warn);
    Serial.print(" | ");

    Serial.println();
};