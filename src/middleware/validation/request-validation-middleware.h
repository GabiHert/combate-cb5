
#ifndef REQUEST_VALIDATION_MIDDLEWARE_H
#define REQUEST_VALIDATION_MIDDLEWARE_H
#include <Arduino.h>
#include "domain/builder/check-sum-builder.h"
#include <string.h>
using namespace std;

class RequestValidationMiddleware
{
private:
    CheckSumBuilder checkSumBuilder;
    bool validateProtocol(string request);
    bool validateCheckSum(string request);

public:
    bool validate(string request);
    RequestValidationMiddleware();
};

#endif