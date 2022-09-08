#ifndef VALIDATION_ERROR_H
#define VALIDATION_ERROR_H
#include <iostream>
#include <Arduino.h>
#include "error-type.h"
#include "error.h"

class ValidationError : public Error
{
private:
    string _message;
    ERROR_TYPE errorType;

public:
    ValidationError(string message)
    {
        this->errorType.description = "Validation error";
        this->errorType.errorCode[0] = '0';
        this->errorType.errorCode[1] = '0';
        this->errorType.errorCode[2] = '1';
        this->_message = message;
        Error(this->errorType, this->_message);
    }

    string message() { return _message; };
};
#endif