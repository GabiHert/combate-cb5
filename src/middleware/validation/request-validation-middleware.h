
#ifndef REQUEST_VALIDATION_MIDDLEWARE_H
#define REQUEST_VALIDATION_MIDDLEWARE_H
#include <Arduino.h>
#include "domain/builder/check-sum-builder.h"
#include <string.h>
#include <iostream>
#include "exceptions/error-type.h"
using namespace std;

class RequestValidationMiddleware
{
private:
    CheckSumBuilder checkSumBuilder;
    bool validateProtocol(string request);
    bool validateCheckSum(string request);

public:
    pair<bool, ERROR_TYPE *> validate(string request);
    bool validateSimpleV4(string request);
    RequestValidationMiddleware();
};

#endif