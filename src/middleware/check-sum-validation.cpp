#include "utils/utils.h"
#include "middleware/middleware.h"
#include <Arduino.h>

bool CheckSumValidation::validate(String target, String received)
{
    loggerInfo("CheckSumValidation.validate", "Process started", "receivedSize: " + String(received) + " target: " + String(target));
    unsigned int receivedSize = sizeof(target);

    if (String(receivedSize) != target)
    {
        loggerError("CheckSumValidation.validate", "Process error", "receivedSize: " + String(receivedSize) + " target: " + String(target));
        return false;
    };
    loggerInfo("CheckSumValidation.validate", "Process finished", "receivedSize: " + String(received) + " target: " + String(target));
    return true;
}