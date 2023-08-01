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
    char _initializer[2];
    char _errorCode[3];
    char _status;
    string _gpsData;
    char _checkSum;

public:
    ResponseDto(Cb cb);
    ResponseDto(Cb cb, char *errorCode);
    ResponseDto(){};
    char *getInitializer();
    char *getErrorCode();
    string getGpsData();
    char getStatus();
};

#endif