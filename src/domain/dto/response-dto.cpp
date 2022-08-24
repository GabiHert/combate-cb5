#include "domain/dto/response-dto.h"
#include "utils/utils.h"
ResponseDto::ResponseDto(Cb cb)
{
    this->_initializer = "&";
    this->_errorCode = "000";
    this->_whellBoltsCount[0] = cb.getWhellBoltsCountDecimal();
    this->_whellBoltsCount[1] = cb.getWhellBoltsCountUnit();
    this->_gpsData = cb.gps.getLocation();
};

ResponseDto::ResponseDto(Cb cb, String errorCode)
{
    this->_initializer = "&";
    if (errorCode.length() > 3)
    {
        // TODO: Throw error
    }
    this->_errorCode = errorCode;
    this->_whellBoltsCount[0] = cb.getWhellBoltsCountDecimal();
    this->_whellBoltsCount[1] = cb.getWhellBoltsCountUnit();
    this->_gpsData = cb.gps.getLocation();
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
