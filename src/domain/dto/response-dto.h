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
    char _whellBoltsCount[2];
    string _initializer;
    char _errorCode[3];
    string _status;
    string _gpsData;
    string _checkSum;
    string _extraChar;

public:
    ResponseDto(Cb cb);
    ResponseDto(Cb cb, char errorCode[3]);
    ResponseDto(char errorCode[3], char whellBoltsCount[2], string gpsLocation);
    ResponseDto(string status, char whellBoltsCount[2], string gpsLocation);
    ResponseDto(){};
    string getInitializer();
    char *getErrorCode();
    char *getWhellBoltsCount();
    string getGpsData();
    string getStatus();
};

#endif