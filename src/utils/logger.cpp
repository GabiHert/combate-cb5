#include <Arduino.h>
#include "utils/utils.h"
#include "interfaces/system-interface.h"

void loggerInfo(String event, String details, String message)
{

    Serial.println("INFO - :: -  event: " + event + " |  details: " + details + " | message:" + message);
    Serial.println();
};

void loggerError(String event, String details, String error)
{

    Serial.println("ERROR - :: -  event: " + event + " |  details: " + details + " | error:" + error);
    Serial.println();
};

void loggerWarn(String event, String details, String warn)
{
    Serial.println("WARN - :: -  event: " + event + " |  details: " + details + " | warn:" + warn);

    Serial.println();
};