#ifndef ERROR_OR_ResponseModel_H
#define ERROR_OR_ResponseModel_H
#include "exceptions/error-type.h"
#include "domain/model/response-model.h"

class ErrorOrResponseModel
{
private:
    ResponseModel _responseModel;
    ERROR_TYPE _error;
    bool _isError;

public:
    ErrorOrResponseModel(){};
    ErrorOrResponseModel(ERROR_TYPE error) : _error(error), _isError(true){};
    ErrorOrResponseModel(ResponseModel responseModel) : _responseModel(responseModel), _isError(false){};

    bool isError() { return this->_isError; };
    ResponseModel getResponseModel() { return this->_responseModel; };
    ERROR_TYPE getError() { return this->_error; }
};

#endif