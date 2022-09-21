#ifndef ERROR_OR_CHAR_H
#define ERROR_OR_CHAR_H
#include "exceptions/error-type.h"

class ErrorOrChar
{
private:
    char _char;
    ERROR_TYPE _error;
    bool _isError;

public:
    ErrorOrChar(){};
    ErrorOrChar(ERROR_TYPE error) : _error(error), _isError(true){};
    ErrorOrChar(char c) : _char(c), _isError(false){};

    bool isError() { return this->_isError; };
    char getChar() { return this->_char; };
    ERROR_TYPE getError() { return this->_error; }
};

#endif