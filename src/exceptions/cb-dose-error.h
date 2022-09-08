#include <iostream>
#include <Arduino.h>
#include "error-type.h"
#include "error.h"

class CbDoseError : public Error
{
private:
    string _message;
    ERROR_TYPE errorType;

public:
    CbDoseError(string message)
    {
        this->errorType.description = "Dose process error";
        this->errorType.errorCode[0] = '0';
        this->errorType.errorCode[1] = '0';
        this->errorType.errorCode[2] = '2';
        this->_message = message;
        Error(this->errorType, this->_message);
    }

    string message() { return _message; };
};