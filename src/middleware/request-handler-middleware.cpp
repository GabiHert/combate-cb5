#include "middleware/request-handler-middleware.h"
#include <Arduino.h>
#include "utils/utils.h"

int RequestHandlerMiddleware::handle(String request)
{
    loggerInfo("RequestHandler.handle", "Process started", "request: " + String(request));

    loggerInfo("RequestHandler.handle", "Process finished");

    return 1;
};