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
    char _errorCode[3];
    char _status;
    string _gpsData;
    char _checkSum;
    bool _leftApplicatorConnected;
    bool _centerApplicatorConnected;
    bool _rightApplicatorConnected;

public:
    ResponseModel(ResponseDto *responseDto);
    ResponseModel(char *errorCode);
    ResponseModel(ResponseDto *responseDto, char *errorCode);
    ResponseModel();
    string toString();
    string getErrorCode();
    string getGpsData();
    bool getLeftApplicatorConnected();
    bool getCenterApplicatorConnected();
    bool getRightApplicatorConnected();
};

#endif