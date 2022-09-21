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
    this->_whellBoltsCount[0] = cb.getWhellBoltsCountDecimal();
    this->_whellBoltsCount[1] = cb.getWhellBoltsCountUnit();
    this->_gpsData = cb.getLocation();
    loggerInfo("ResponseDto", "whellBoltsCount assigned", to_string(this->_whellBoltsCount[0]) + to_string(this->_whellBoltsCount[1]));

    loggerInfo("ResponseDto", "Process finished - constructor");
};

ResponseDto::ResponseDto(string errorCode, char whellBoltsCount[2], string gpsLocation)
{
    loggerInfo("ResponseDto", "Process started - constructor");
    this->_initializer = "&";
    this->_status = CONFIG().PROTOCOL_STATUS_ERROR;
    this->setErrorCode(errorCode);
    this->_whellBoltsCount[0] = whellBoltsCount[0];
    this->_whellBoltsCount[1] = whellBoltsCount[1];

    this->_gpsData = gpsLocation;
    loggerInfo("ResponseDto", "gpsData assigned", this->_gpsData);

    loggerInfo("ResponseDto", "Process finished - constructor");
};

ResponseDto::ResponseDto(char whellBoltsCount[2], string status, string gpsLocation)
{
    loggerInfo("ResponseDto", "Process started - constructor");
    this->_initializer = "&";
    this->_status = status;
    this->setErrorCode("000");
    this->_whellBoltsCount[0] = whellBoltsCount[0];
    this->_whellBoltsCount[1] = whellBoltsCount[1];

    this->_gpsData = gpsLocation;
    loggerInfo("ResponseDto", "gpsData assigned", this->_gpsData);

    loggerInfo("ResponseDto", "Process finished - constructor");
};

ResponseDto::ResponseDto(Cb cb, string errorCode)
{
    loggerInfo("ResponseDto", "Process started - constructor", "errorCode: " + errorCode);

    this->_initializer = "&";
    this->setErrorCode(errorCode);
    this->_whellBoltsCount[0] = cb.getWhellBoltsCountDecimal();
    this->_whellBoltsCount[1] = cb.getWhellBoltsCountUnit();
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

char *ResponseDto::getWhellBoltsCount()
{
    return this->_whellBoltsCount;
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