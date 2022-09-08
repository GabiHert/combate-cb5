#include "domain/model/response-model.h"
#include "utils/utils.h"
ResponseModel::ResponseModel(ResponseDto responseDto)
{
    loggerInfo("ResponseModel", "Process started - constructor");

    this->_initializer = responseDto.getInitializer();
    this->_status = responseDto.getStatus();
    this->_errorCode[0] = responseDto.getErrorCode()[0];
    this->_errorCode[1] = responseDto.getErrorCode()[1];
    this->_errorCode[2] = responseDto.getErrorCode()[2];
    this->_whellBoltsCount[0] = responseDto.getWhellBoltsCount()[0];
    this->_whellBoltsCount[1] = responseDto.getWhellBoltsCount()[1];
    this->_gpsData = responseDto.getGpsData();
    this->_lineFeed = CONFIG().PROTOCOL_LF;
    this->_carriageReturn = CONFIG().PROTOCOL_CR;
    this->_extraChar = "xxx";
    loggerInfo("ResponseModel", "Process finished - constructor");
};

ResponseModel::ResponseModel(char errorCode[3])
{
    loggerInfo("ResponseModel", "Process started - constructor");

    this->_initializer = "&";
    this->_status = CONFIG().PROTOCOL_STATUS_ERROR;
    this->_errorCode[0] = errorCode[0];
    this->_errorCode[1] = errorCode[1];
    this->_errorCode[2] = errorCode[2];

    this->_whellBoltsCount[0] = 0;
    this->_whellBoltsCount[1] = 0;
    this->_gpsData = " ";
    this->_lineFeed = CONFIG().PROTOCOL_LF;
    this->_carriageReturn = CONFIG().PROTOCOL_CR;
    this->_extraChar = "xxx";
    loggerInfo("ResponseModel", "Process finished - constructor");
}

string ResponseModel::tostring()
{
    loggerInfo("ResponseModel.tostring", "Process started");
    string response = this->_initializer + this->_whellBoltsCount[0] + this->_whellBoltsCount[1] + this->_status;
    response += this->_errorCode[0] + this->_errorCode[1] + this->_errorCode[2];
    response += this->_extraChar;
    response += this->_checkSumBuilder.build(response);
    response += "," + this->_gpsData;
    response += to_string(this->_carriageReturn) + to_string(this->_lineFeed);
    loggerInfo("ResponseModel.tostring", "Process finished", "response: " + response);

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

char *ResponseModel::getWhellBoltsCount()
{
    return this->_whellBoltsCount;
}

string ResponseModel::getGpsData()
{
    return this->_gpsData;
}
