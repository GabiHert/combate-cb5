#ifndef ERROR_OR_ResponseDto_H
#define ERROR_OR_ResponseDto_H
#include "exceptions/error-type.h"
#include "domain/dto/response-dto.h"

class ErrorOrResponseDto
{
private:
    ResponseDto _responseDto;
    ERROR_TYPE _error;
    bool _isError;

public:
    ErrorOrResponseDto(){};
    ErrorOrResponseDto(ERROR_TYPE error) : _error(error), _isError(true){};
    ErrorOrResponseDto(ResponseDto responseDto) : _responseDto(responseDto), _isError(false){};

    bool isError() { return this->_isError; };
    ResponseDto getResponseDto() { return this->_responseDto; };
    ERROR_TYPE getError() { return this->_error; }
};

#endif