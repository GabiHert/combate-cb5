#ifndef ERROR_OR_RequestModel_H
#define ERROR_OR_RequestModel_H
#include "exceptions/error-type.h"
#include "domain/model/request-model.h"

class ErrorOrRequestModel
{
private:
    RequestModel _requestModel;
    ERROR_TYPE _error;
    bool _isError;

public:
    ErrorOrRequestModel(){};
    ErrorOrRequestModel(ERROR_TYPE error) : _error(error), _isError(true){};
    ErrorOrRequestModel(RequestModel requestModel) : _requestModel(requestModel), _isError(false){};
    bool isError() { return this->_isError; };
    RequestModel getRequestModel() { return this->_requestModel; };
    ERROR_TYPE getError() { return this->_error; }
};

#endif