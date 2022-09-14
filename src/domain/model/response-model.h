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
    char _errorCode[3];
    string _status;
    char _whellBoltsCount[2];
    string _gpsData;
    string _checkSum;
    string _extraChar;
    int _lineFeed;
    int _carriageReturn;

public:
    ResponseModel(ResponseDto responseDto);
    ResponseModel(char errorCode[3]);
    ResponseModel(){};
    string tostring();
    string getInitializer();
    string getErrorCode();
    char *getWhellBoltsCount();
    string getGpsData();
};

#endif