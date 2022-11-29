#ifndef ERROR_OR_BOOL_VECTOR_H
#define ERROR_OR_BOOL_VECTOR_H
#include "exceptions/error-type.h"
#include <vector>
using namespace std;

class ErrorOrBoolVector
{
private:
    vector<bool> _boolVector;
    ERROR_TYPE _error;
    bool _isError;

public:
    ErrorOrBoolVector(){};
    ErrorOrBoolVector(ERROR_TYPE error) : _error(error), _isError(true){};
    ErrorOrBoolVector(vector<bool> b) : _boolVector(b), _isError(false){};

    bool isError() { return this->_isError; };
    vector<bool> getBoolVector() { return this->_boolVector; };
    ERROR_TYPE getError() { return this->_error; }
};

#endif