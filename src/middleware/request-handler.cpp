#include "utils/utils.h"
#include <Arduino.h>
#include "middleware.h"

int RequestHandler::handle(String request)
{
    loggerInfo("RequestHandler.handle", "Process started", "request: " + String(request));

    loggerInfo("RequestHandler.handle", "Process finished");

    return 1;
};