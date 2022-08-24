#ifndef RESPONSE_MODEL_H
#define RESPONSE_MODEL_H
#include "domain/cb/cb.h"
#include <Arduino.h>
#include "domain/builder/check-sum-builder.h"
#include "config/config.h"
#include "domain/dto/response-dto.h"

class ResponseModel {
private:
CheckSumBuilder _checkSumBuilder;
String _initializer;
String _errorCode;
char _whellBoltsCount[2];
String _gpsData;
String _checkSum;
String _extraChar;
int _lineFeed;
int _carriageReturn;

public:
ResponseModel::ResponseModel(ResponseDto ResponseDto);
ResponseModel::ResponseModel(String errorCode);
ResponseModel::ResponseModel();
String toString();
String getInitializer();
String getErrorCode();
char* getWhellBoltsCount();
String getGpsData();
};

#endif