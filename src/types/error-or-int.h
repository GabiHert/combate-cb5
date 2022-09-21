#ifndef ERROR_OR_INT_H
#define ERROR_OR_INT_H
#include "exceptions/error-type.h"

class ErrorOrInt
{
private:
    int _int;
    ERROR_TYPE _error;
    bool _isError;

public:
    ErrorOrInt(){};
    ErrorOrInt(ERROR_TYPE error) : _error(error), _isError(true){};
    ErrorOrInt(int i) : _int(i), _isError(false){};

    bool isError() { return this->_isError; };
    int getInt() { return this->_int; };
    ERROR_TYPE getError() { return this->_error; }
};

#endif