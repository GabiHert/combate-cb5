#ifndef RESPONSE_MODEL_H
#define RESPONSE_MODEL_H
#include "domain/cb/cb.h"
#include <Arduino.h>
#include "domain/builder/check-sum-builder.h"
#include "config/config.h"
#include "domain/dto/response-dto.h"
#include <string.h>
using namespace std;

class ResponseModel
{
private:
    CheckSumBuilder _checkSumBuilder;
    string _initializer;
    string _errorCode;
    string _status;
    string _gpsData;
    string _checkSum;
    string _extraChar;

public:
    ResponseModel(ResponseDto responseDto);
    ResponseModel(string errorCode);
    ResponseModel(ResponseDto responseDto, string errorCode);
    ResponseModel();
    string toString();
    string getInitializer();
    string getErrorCode();
    string getGpsData();
    void setErrorCode(string errorCode);
};

#endif