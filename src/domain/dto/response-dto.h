#ifndef RESPONSE_DTO_H
#define RESPONSE_DTO_H
#include "domain/cb/cb.h"
#include <Arduino.h>
#include "domain/builder/check-sum-builder.h"
#include "config/config.h"

class ResponseDto
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
    ResponseDto(Cb cb);
    ResponseDto(Cb cb, string errorCode);
    ResponseDto(){};
    string getInitializer();
    string getErrorCode();
    string getGpsData();
    string getStatus();
    void setErrorCode(string errorCode);
};

#endif