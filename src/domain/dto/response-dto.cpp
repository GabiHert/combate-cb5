#include "domain/dto/response-dto.h"
#include "utils/utils.h"
#include <Arduino.h>
#include <string.h>
using namespace std;

ResponseDto::ResponseDto(Cb cb)
{
    loggerInfo("ResponseDto", "Process started - constructor");
    this->_initializer = "&";
    this->_status = cb.getStatus();
    this->setErrorCode("000");
    this->_gpsData = cb.getLocation();
    loggerInfo("ResponseDto", "Process finished - constructor");
};

ResponseDto::ResponseDto(Cb cb, string errorCode)
{
    logger(errorCode);
    loggerInfo("ResponseDto", "Process started - constructor", "errorCode: " + errorCode);
    this->_initializer = "&";
    this->_status = cb.getStatus();
    this->setErrorCode(errorCode);
    this->_gpsData = cb.getLocation();
    loggerInfo("ResponseDto", "Process finished - constructor");
}

string ResponseDto::getInitializer()
{
    return this->_initializer;
}

string ResponseDto::getErrorCode()
{
    return this->_errorCode;
}


string ResponseDto::getGpsData()
{
    return this->_gpsData;
}

string ResponseDto::getStatus()
{
    return this->_status;
}

void ResponseDto::setErrorCode(string errorCode)
{
    if (errorCode.length() != 3)
    {
        // throw error
    }

    this->_errorCode = errorCode;
}