#include <Arduino.h>
#include "utils/utils.h"
#include "interfaces/system-interface.h"

void loggerInfo(string event, string details, string message)
{
    String _event = stdStringToArduinoString(event), _details = stdStringToArduinoString(details), _message = stdStringToArduinoString(message);

    Serial.println("INFO - :: -  event: " + _event + " |  details: " + _details + " | message: " + _message);

    Serial.println("");
};

void loggerError(string event, string details, string error)
{
    String _event = stdStringToArduinoString(event), _details = stdStringToArduinoString(details), _error = stdStringToArduinoString(error);

    Serial.println("ERROR - :: -  event: " + _event + " |  details: " + _details + " | error: " + _error);
    Serial.println("");
};

void loggerWarn(string event, string details, string warn)
{

    String _event = stdStringToArduinoString(event), _details = stdStringToArduinoString(details), _warn = stdStringToArduinoString(warn);

    Serial.println("WARN - :: -  event: " + _event + " |  details: " + _details + " | warn: " + _warn);

    Serial.println("");
};
