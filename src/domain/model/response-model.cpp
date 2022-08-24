#include "domain/model/response-model.h"
#include "utils/utils.h"
ResponseModel::ResponseModel(ResponseDto responseDto)
{
    this->_initializer = responseDto.getInitializer();
    this->_errorCode = responseDto.getErrorCode();
    this->_whellBoltsCount[0] = responseDto.getWhellBoltsCount()[0];
    this->_whellBoltsCount[1] = responseDto.getWhellBoltsCount()[1];
    this->_gpsData = responseDto.getGpsData();
    this->_lineFeed = config.PROTOCOL_LF;
    this->_carriageReturn = config.PROTOCOL_CR;
};

ResponseModel::ResponseModel(String errorCode)
{
    if (errorCode.length() > 3)
    {
        // TODO: Throw error
    }
}

String ResponseModel::toString()
{
    loggerInfo("ResponseModel.toString", "Process started");
    String response = this->_initializer + this->_errorCode + this->_extraChar;
    response += this->_whellBoltsCount[0] + this->_whellBoltsCount[1];

    response += this->_checkSumBuilder.build(response);
    response += "," + this->_gpsData;
    response += String(this->_carriageReturn) + String(this->_lineFeed);
    loggerInfo("ResponseModel.toString", "Process finished");

    return response;
}

String ResponseModel::getInitializer()
{
    return this->_initializer;
}

String ResponseModel::getErrorCode()
{
    return this->_errorCode;
}

char *ResponseModel::getWhellBoltsCount()
{
    return this->_whellBoltsCount;
}

String ResponseModel::getGpsData()
{
    return this->_gpsData;
}
