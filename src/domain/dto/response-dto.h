#ifndef RESPONSE_DTO_H
#define RESPONSE_DTO_H
#include "domain/cb/cb.h"
#include <Arduino.h>
#include "domain/builder/check-sum-builder.h"
#include "config/config.h"

class ResponseDto
{
private:
    char _errorCode[3];
    char _status;
    string _gpsData;
    char _checkSum;
    bool _leftApplicatorConnected;
    bool _centerApplicatorConnected;
    bool _rightApplicatorConnected;

public:
    ResponseDto(Cb cb, string gpsData, char status);
    ResponseDto(Cb cb, string gpsData, char *errorCode);
    ResponseDto(){};
    char *getErrorCode();
    string getGpsData();
    char getStatus();
    bool getLeftApplicatorConnected();
    bool getCenterApplicatorConnected();
    bool getRightApplicatorConnected();
};

#endif