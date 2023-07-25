#include <Arduino.h>
#include "utils/utils.h"
#include "infra/system/system-interface.h"
#include "config/config.h"

void loggerInfo(string event, string details, string message)
{
    Serial.println("INFO - :: -  event: " + stdStringToArduinoString(event) + " |  details: " + stdStringToArduinoString(details) + " | message: " + stdStringToArduinoString(message));
};

void loggerError(string event, string details, string error)
{
    Serial.println("ERROR - :: -  event: " + stdStringToArduinoString(event) + " |  details: " + stdStringToArduinoString(event) + " | error: " + stdStringToArduinoString(error));
};

void logger(string message)
{

    String _message = stdStringToArduinoString(message);
    Serial.println(_message);
} // 1312093
