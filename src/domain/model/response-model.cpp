#include "domain/model/response-model.h"
#include "utils/utils.h"
ResponseModel::ResponseModel(ResponseDto responseDto)
{
    loggerInfo("ResponseModel", "Process started - constructor");

    this->_initializer = responseDto.getInitializer();
    this->_status = responseDto.getStatus();
    this->setErrorCode(responseDto.getErrorCode());
    this->_gpsData = responseDto.getGpsData();
    this->_extraChar = "xxx";
    loggerInfo("ResponseModel", "Process finished - constructor");
};

ResponseModel::ResponseModel(string errorCode)
{
    logger(errorCode);
    loggerInfo("ResponseModel", "Process started - constructor");

    this->_initializer = "&";
    this->_status = CONFIG_PROTOCOL_STATUS_ERROR;
    this->_errorCode = errorCode;
    this->_gpsData = " ";
    this->_extraChar = "xxx";
    loggerInfo("ResponseModel", "Process finished - constructor");
}

ResponseModel::ResponseModel(ResponseDto responseDto, string errorCode)
{
    logger(errorCode);
    this->_initializer = "&";
    this->_status = CONFIG_PROTOCOL_STATUS_ERROR;
    this->_errorCode = errorCode;

    this->_gpsData = responseDto.getGpsData();
    this->_extraChar = "xxx";
    loggerInfo("ResponseModel", "Process finished - constructor");
}

ResponseModel::ResponseModel()
{
    this->_gpsData = " ";
    this->_extraChar = "xxx";
}

string ResponseModel::toString()
{
    loggerInfo("ResponseModel.tostring", "Process started");
    string response;
    response += "0";
    response += "0";
    response += this->_status;
    response += this->_errorCode;
    response += this->_extraChar;
    response += this->_checkSumBuilder.build(response);
    response += ",";
    response += this->_gpsData;
    response += CONFIG_PROTOCOL_CR;
    response += CONFIG_PROTOCOL_LF;
    response = this->_initializer + response;

    return response;
}

string ResponseModel::getInitializer()
{
    return this->_initializer;
}

string ResponseModel::getErrorCode()
{
    return this->_errorCode;
}

string ResponseModel::getGpsData()
{
    return this->_gpsData;
}

void ResponseModel::setErrorCode(string errorCode)
{

    this->_errorCode = errorCode;
}