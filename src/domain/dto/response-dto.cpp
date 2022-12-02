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
    this->_wheelBoltsCount[0] = cb.getWheelBoltsCountDecimal();
    this->_wheelBoltsCount[1] = cb.getWheelBoltsCountUnit();
    this->_gpsData = cb.getLocation();
    loggerInfo("ResponseDto", "wheelBoltsCount assigned", to_string(this->_wheelBoltsCount[0]) + to_string(this->_wheelBoltsCount[1]));

    loggerInfo("ResponseDto", "Process finished - constructor");
};

ResponseDto::ResponseDto(string errorCode, char wheelBoltsCount[2], string gpsLocation)
{
    loggerInfo("ResponseDto", "Process started - constructor");
    this->_initializer = "&";
    this->_status = CONFIG_PROTOCOL_STATUS_ERROR;
    this->setErrorCode(errorCode);
    this->_wheelBoltsCount[0] = wheelBoltsCount[0];
    this->_wheelBoltsCount[1] = wheelBoltsCount[1];

    this->_gpsData = gpsLocation;
    loggerInfo("ResponseDto", "gpsData assigned", this->_gpsData);

    loggerInfo("ResponseDto", "Process finished - constructor");
};

ResponseDto::ResponseDto(char wheelBoltsCount[2], string status, string gpsLocation)
{
    loggerInfo("ResponseDto", "Process started - constructor");
    this->_initializer = "&";
    this->_status = status;
    this->setErrorCode("000");
    this->_wheelBoltsCount[0] = wheelBoltsCount[0];
    this->_wheelBoltsCount[1] = wheelBoltsCount[1];

    this->_gpsData = gpsLocation;
    loggerInfo("ResponseDto", "gpsData assigned", this->_gpsData);

    loggerInfo("ResponseDto", "Process finished - constructor");
};

ResponseDto::ResponseDto(Cb cb, string errorCode)
{
    loggerInfo("ResponseDto", "Process started - constructor", "errorCode: " + errorCode);

    this->_initializer = "&";
    this->setErrorCode(errorCode);
    this->_wheelBoltsCount[0] = cb.getWheelBoltsCountDecimal();
    this->_wheelBoltsCount[1] = cb.getWheelBoltsCountUnit();
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

char *ResponseDto::getWheelBoltsCount()
{
    return this->_wheelBoltsCount;
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