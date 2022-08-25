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
    String _initializer;
    String _errorCode;
    char _whellBoltsCount[2];
    String _gpsData;
    String _checkSum;
    String _extraChar;

public:
    ResponseDto(Cb cb);
    ResponseDto(Cb cb, String errorCode);
    ResponseDto(){};
    String getInitializer();
    String getErrorCode();
    char *getWhellBoltsCount();
    String getGpsData();
};

#endif