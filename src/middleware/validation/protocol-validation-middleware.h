#include <Arduino.h>
#ifndef PROTOCOL_VALIDATION_MIDDLEWARE_H
#define PROTOCOL_VALIDATION_MIDDLEWARE_H

class ProtocolValidationMiddleware
{
public:
    bool validate(String request);
};

#endif // PROTOCOL_VALIDATION_MIDDLEWARE_H
#