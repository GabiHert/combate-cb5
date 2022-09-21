#ifndef ERROR_OR_RequestDto_H
#define ERROR_OR_RequestDto_H
#include "exceptions/error-type.h"
#include "domain/dto/request-dto.h"

class ErrorOrRequestDto
{
private:
    RequestDto _requestDto;
    ERROR_TYPE _error;
    bool _isError;

public:
    ErrorOrRequestDto(){};
    ErrorOrRequestDto(ERROR_TYPE error) : _error(error), _isError(true){};
    ErrorOrRequestDto(RequestDto requestDto) : _requestDto(requestDto), _isError(false){};
    bool isError()
    {
        return this->_isError;
    };
    RequestDto getRequestDto() { return this->_requestDto; };
    ERROR_TYPE getError() { return this->_error; }
};

#endif