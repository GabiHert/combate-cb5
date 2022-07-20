#include <Arduino.h>

#ifndef CHECKSUM_VALIDATION_MIDDLEWARE_H
#define CHECKSUM_VALIDATION_MIDDLEWARE_H

class CheckSumValidationMiddleware
{
public:
    bool validate(String target, String received);
};

#endif // CHECKSUM_VALIDATION_MIDDLEWARE_H