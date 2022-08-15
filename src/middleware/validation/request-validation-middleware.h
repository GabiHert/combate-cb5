
#ifndef REQUEST_VALIDATION_MIDDLEWARE
#define APP_H
#include <Arduino.h>
#include "middleware/builder/check-sum-builder.h"

class RequestValidationMiddleware
{
private:
    CheckSumBuilder checkSumBuilder;
    bool validateProtocol(String request);
    bool validateCheckSum(String request);

public:
    bool validate(String request);
    RequestValidationMiddleware();
};

#endif