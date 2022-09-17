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
    this->_errorCode[0] = '0';
    this->_errorCode[1] = '0';
    this->_errorCode[2] = '0';
    this->_whellBoltsCount[0] = cb.getWhellBoltsCountDecimal();
    this->_whellBoltsCount[1] = cb.getWhellBoltsCountUnit();
    this->_gpsData = cb.getGpsData();
    loggerInfo("ResponseDto", "whellBoltsCount assigned", to_string(this->_whellBoltsCount[0]) + to_string(this->_whellBoltsCount[1]));

    loggerInfo("ResponseDto", "Process finished - constructor");
};

ResponseDto::ResponseDto(char errorCode[3], char whellBoltsCount[2], string gpsLocation)
{
    loggerInfo("ResponseDto", "Process started - constructor");
    this->_initializer = "&";
    this->_status = CONFIG().PROTOCOL_STATUS_ERROR;
    this->_errorCode[0] = errorCode[0];
    this->_errorCode[1] = errorCode[1];
    this->_errorCode[2] = errorCode[2];
    this->_whellBoltsCount[0] = whellBoltsCount[0];
    this->_whellBoltsCount[1] = whellBoltsCount[1];

    this->_gpsData = gpsLocation;
    loggerInfo("ResponseDto", "gpsData assigned", this->_gpsData);

    loggerInfo("ResponseDto", "Process finished - constructor");
};

ResponseDto::ResponseDto(string status, char whellBoltsCount[2], string gpsLocation)
{
    loggerInfo("ResponseDto", "Process started - constructor");
    this->_initializer = "&";
    this->_status = status;
    this->_errorCode[0] = '0';
    this->_errorCode[1] = '0';
    this->_errorCode[2] = '0';
    this->_whellBoltsCount[0] = whellBoltsCount[0];
    this->_whellBoltsCount[1] = whellBoltsCount[1];

    this->_gpsData = gpsLocation;
    loggerInfo("ResponseDto", "gpsData assigned", this->_gpsData);

    loggerInfo("ResponseDto", "Process finished - constructor");
};

ResponseDto::ResponseDto(Cb cb, char errorCode[3])
{
    loggerInfo("ResponseDto", "Process started - constructor", "errorCode: " + to_string(errorCode[0]) + to_string(errorCode[1]) + to_string(errorCode[2]));

    this->_initializer = "&";
    this->_errorCode[0] = errorCode[0];
    this->_errorCode[1] = errorCode[1];
    this->_errorCode[2] = errorCode[2];
    this->_whellBoltsCount[0] = cb.getWhellBoltsCountDecimal();
    this->_whellBoltsCount[1] = cb.getWhellBoltsCountUnit();
    this->_gpsData = cb.getGpsData();
    loggerInfo("ResponseDto", "Process finished - constructor");
}

string ResponseDto::getInitializer()
{
    return this->_initializer;
}

char *ResponseDto::getErrorCode()
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