#ifndef ERROR_H
#define ERROR_H
#include <iostream>
#include <Arduino.h>
#include "error-type.h"
#include <string.h>
using namespace std;

class Error : public std::exception
{
private:
    string _message;
    ERROR_TYPE _errorType;

public:
    Error(ERROR_TYPE errorType, string message)
    {
        this->_errorType = errorType;
        this->_message = message;
        // FLAG: is this valid?  std::exception(message);
    }
    Error() {}

    string message() { return this->_message; };
    ERROR_TYPE errorType() { return this->_errorType; };
};
#endif