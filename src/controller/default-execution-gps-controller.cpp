#include "controller/default-execution-gps-controller.h"
#include <Arduino.h>
#include "utils/utils.h"
#include "domain/model/cb.h"

void DefaultExecutionGpsController::execute(Cb cb)
{
    loggerInfo("DefaultExecutionController", "Process started");
    String location = cb.gps.getLocation();
    //  TODO: encode location with the other cb info
    //  TODO: repond
    //  TODO: wait
    loggerInfo("DefaultExecutionController", "Process finished");
};