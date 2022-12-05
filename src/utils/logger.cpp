#include <Arduino.h>
#include "utils/utils.h"
#include "interfaces/system-interface.h"
#include "config/config.h"

void loggerInfo(string event, string details, string message)
{
    String _event = stdStringToArduinoString(event), _details = stdStringToArduinoString(details), _message = stdStringToArduinoString(message);

    if (_message.length() == 0)
        _message = " ";
    // Serial.println("INFO - :: -  event: " + _event + " |  details: " + _details + " | message: " + _message);
    // Serial.println("");
};

void loggerError(string event, string details, string error)
{

    String _event = stdStringToArduinoString(event), _details = stdStringToArduinoString(details), _error = stdStringToArduinoString(error);

    if (_error.length() == 0)
        _error = " ";

    Serial.println("ERROR - :: -  event: " + _event + " |  details: " + _details + " | error: " + _error);
    Serial.println("");
};

void loggerWarn(string event, string details, string warn)
{

    String _event = stdStringToArduinoString(event), _details = stdStringToArduinoString(details), _warn = stdStringToArduinoString(warn);

    if (_warn.length() == 0)
        _warn = " ";

    // Serial.println("WARN - :: -  event: " + _event + " |  details: " + _details + " | warn: " + _warn);

    // Serial.println("");
};

void logger(string message)
{

    String _message = stdStringToArduinoString(message);
    // Serial.println(_message);
}