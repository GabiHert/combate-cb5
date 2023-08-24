#include "domain/model/response-model.h"
#include "utils/utils.h"
ResponseModel::ResponseModel(ResponseDto *responseDto)
{

    this->_status = responseDto->getStatus();
    strncpy(this->_errorCode, responseDto->getErrorCode(), 3);
    this->_gpsData = responseDto->getGpsData();
    this->_leftApplicatorConnected = responseDto->getLeftApplicatorConnected();
    this->_centerApplicatorConnected = responseDto->getCenterApplicatorConnected();
    this->_rightApplicatorConnected = responseDto->getRightApplicatorConnected();
};

ResponseModel::ResponseModel(char *errorCode)
{
    this->_status = CONFIG_PROTOCOL_STATUS_ERROR;
    strncpy(this->_errorCode, errorCode, 3);
}

ResponseModel::ResponseModel(ResponseDto *responseDto, char *errorCode)
{

    this->_status = CONFIG_PROTOCOL_STATUS_ERROR;
    strncpy(this->_errorCode, errorCode, 3);
    this->_gpsData = responseDto->getGpsData();
    this->_leftApplicatorConnected = responseDto->getLeftApplicatorConnected();
    this->_centerApplicatorConnected = responseDto->getCenterApplicatorConnected();
    this->_rightApplicatorConnected = responseDto->getRightApplicatorConnected();
}

ResponseModel::ResponseModel()
{
}

string ResponseModel::toString()
{
    //loggerInfo("ResponseModel.tostring", "Process started");
    string response = "";
    response += this->_status;
    response += this->_errorCode[0];
    response += this->_errorCode[1];
    response += this->_errorCode[2];
    response += this->_leftApplicatorConnected ? '1' : '0';
    response += this->_centerApplicatorConnected ? '1' : '0';
    response += this->_rightApplicatorConnected ? '1' : '0';
    response += this->_checkSumBuilder.build(response);
    response += ",";
    response += this->_gpsData;
    response += CONFIG_PROTOCOL_CR;
    response += CONFIG_PROTOCOL_LF;

    response = CONFIG_PROTOCOL_RESPONSE_HEADER + response;

    //loggerInfo("ResponseModel.tostring", "Process finished", response);
    return response;
}

string ResponseModel::getErrorCode()
{
    return this->_errorCode;
}

string ResponseModel::getGpsData()
{
    return this->_gpsData;
}

bool ResponseModel::getLeftApplicatorConnected()
{
    return this->_leftApplicatorConnected;
};

bool ResponseModel::getCenterApplicatorConnected()
{
    return this->_centerApplicatorConnected;
};

bool ResponseModel::getRightApplicatorConnected()
{
    return this->_rightApplicatorConnected;
};