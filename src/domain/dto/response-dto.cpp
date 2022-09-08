#include "domain/dto/response-dto.h"
#include "utils/utils.h"
#include <Arduino.h>
#include <string.h>
using namespace std;

ResponseDto::ResponseDto(Cb cb)
{
    loggerInfo("ResponseDto", "Process started - constructor");
    this->_initializer = "&";
    this->_status = "S";
    this->_errorCode[0] = '0';
    this->_errorCode[1] = '0';
    this->_errorCode[2] = '0';
    this->_whellBoltsCount[0] = cb.getWhellBoltsCountDecimal();
    this->_whellBoltsCount[1] = cb.getWhellBoltsCountUnit();
    loggerInfo("ResponseDto", "whellBoltsCount assigned", to_string(this->_whellBoltsCount[0]) + to_string(this->_whellBoltsCount[1]));

    this->_gpsData = "$GPRMC,144326.00,A,5107.0017737,N,11402.3291611,W,0.080,323.3,210307,0.0,E,A*20"; // cb.gps.getLocation();
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
    this->_gpsData = cb.gps.getLocation();
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