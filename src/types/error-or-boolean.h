#ifndef ERROR_OR_BOOL_H
#define ERROR_OR_BOOL_H
#include "exceptions/error-type.h"
#include <iostream>

class ErrorOrBool
{
private:
    bool _bool;
    ERROR_TYPE _error;
    bool _isError;

public:
    ErrorOrBool(){};
    ErrorOrBool(ERROR_TYPE error) : _error(error), _isError(true){};
    ErrorOrBool(bool b) : _bool(b), _isError(false){};

    bool isError() { return this->_isError; };
    bool getBool() { return this->_bool; };
    ERROR_TYPE getError() { return this->_error; }
};

#endif