#include "domain/dto/response-dto.h"
#include "utils/utils.h"
#include <Arduino.h>
#include <string.h>
using namespace std;

ResponseDto::ResponseDto(Cb cb, string gpsData, char status)
{
    this->_status = asciiCharToNumber(status);
    this->_errorCode[0] = '0';
    this->_errorCode[1] = '0';
    this->_errorCode[2] = '0';
    this->_gpsData = gpsData;
    this->_leftApplicatorConnected = cb.getPoisonApplicators().at(0)->isConnected();
    this->_centerApplicatorConnected = cb.getPoisonApplicators().at(1)->isConnected();
    this->_rightApplicatorConnected = cb.getPoisonApplicators().at(2)->isConnected();
};

ResponseDto::ResponseDto(Cb cb, string gpsData, char *errorCode)
{
    this->_status = CONFIG_PROTOCOL_STATUS_ERROR;
    strncpy(this->_errorCode, errorCode, 3);
    this->_gpsData = gpsData;
    this->_leftApplicatorConnected = cb.getPoisonApplicators().at(0)->isConnected();
    this->_centerApplicatorConnected = cb.getPoisonApplicators().at(1)->isConnected();
    this->_rightApplicatorConnected = cb.getPoisonApplicators().at(2)->isConnected();
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

bool ResponseDto::getCenterApplicatorConnected()
{
    return this->_centerApplicatorConnected;
}

bool ResponseDto::getLeftApplicatorConnected()
{
    return this->_leftApplicatorConnected;
}

bool ResponseDto::getRightApplicatorConnected()
{
    return this->_rightApplicatorConnected;
}