#ifndef ERROR_OR_STRING_H
#define ERROR_OR_STRING_H
#include "exceptions/error-type.h"
#include "string"
using namespace std;

class ErrorOrString
{
private:
    string _string;
    ERROR_TYPE _error;
    bool _isError;

public:
    ErrorOrString(){};
    ErrorOrString(ERROR_TYPE error) : _error(error), _isError(true){};
    ErrorOrString(string s) : _string(s), _isError(false){};

    bool isError() { return this->_isError; };
    string getString() { return this->_string; };
    ERROR_TYPE getError() { return this->_error; }
};

#endif