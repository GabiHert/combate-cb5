#include "domain/dto/response-dto.h"
#include "utils/utils.h"
#include <Arduino.h>
#include <string.h>
using namespace std;

ResponseDto::ResponseDto(Cb cb)
{
    this->_initializer[0] = '&';
    this->_initializer[1] = '5';
    this->_status = cb.getStatus();
    this->_errorCode[0] = '0';
    this->_errorCode[1] = '0';
    this->_errorCode[2] = '0';
    this->_gpsData = cb.getLocation();
};

ResponseDto::ResponseDto(Cb cb, char *errorCode)
{
    this->_initializer[0] = '&';
    this->_initializer[1] = '5';
    this->_status = cb.getStatus();
    strncpy(this->_errorCode, errorCode, 3);
    this->_gpsData = cb.getLocation();
}

char *ResponseDto::getInitializer()
{
    return this->_initializer;
}

char *ResponseDto::getErrorCode()
{
    return this->_errorCode;
}

string ResponseDto::getGpsData()
{
    return this->_gpsData;
}

char ResponseDto::getStatus()
{
    return this->_status;
}
