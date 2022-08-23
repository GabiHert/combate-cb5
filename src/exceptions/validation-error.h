#include <iostream>
#include <Arduino.h>
#include "error-type.h"

class ValidationError : public std::exception
{
private:
    String _message;
    ERROR_TYPE errorType;

public:
    ValidationError(String message)
    {
        errorType.description = "Validation error";
        errorType.errorCode = "001";
        _message = message;
    }

    String message() { return _message; };
};