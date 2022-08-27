#include "domain/dto/response-dto.h"
#include "utils/utils.h"
ResponseDto::ResponseDto(Cb cb)
{
    loggerInfo("ResponseDto", "Process started - constructor");
    this->_initializer = "&";
    this->_status = "S";
    this->_errorCode = "000";
    this->_whellBoltsCount[0] = cb.getWhellBoltsCountDecimal();
    this->_whellBoltsCount[1] = cb.getWhellBoltsCountUnit();
    loggerInfo("ResponseDto", "whellBoltsCount assigned", String(this->_whellBoltsCount[0]) + String(this->_whellBoltsCount[1]));

    this->_gpsData = "$GPRMC,144326.00,A,5107.0017737,N,11402.3291611,W,0.080,323.3,210307,0.0,E,A*20"; // cb.gps.getLocation();
    loggerInfo("ResponseDto", "gpsData assigned", this->_gpsData);

    loggerInfo("ResponseDto", "Process finished - constructor");
};

ResponseDto::ResponseDto(Cb cb, String errorCode)
{
    loggerInfo("ResponseDto", "Process started - constructor", "errorCode: " + errorCode);

    this->_initializer = "&";
    if (errorCode.length() > 3)
    {
        // TODO: Throw error
    }
    this->_errorCode = errorCode;
    this->_whellBoltsCount[0] = cb.getWhellBoltsCountDecimal();
    this->_whellBoltsCount[1] = cb.getWhellBoltsCountUnit();
    this->_gpsData = cb.gps.getLocation();
    loggerInfo("ResponseDto", "Process finished - constructor");
}

String ResponseDto::getInitializer()
{
    return this->_initializer;
}

String ResponseDto::getErrorCode()
{
    return this->_errorCode;
}

char *ResponseDto::getWhellBoltsCount()
{
    return this->_whellBoltsCount;
}

String ResponseDto::getGpsData()
{
    return this->_gpsData;
}

String ResponseDto::getStatus()
{
    return this->_status;
}