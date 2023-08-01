
#ifndef REQUEST_MODEL_H
#define REQUEST_MODEL_H
#include <Arduino.h>
#include <string>
#include "domain/dto/request-dto.h"

class RequestModel
{
private:
    char _requestType;
    char _rightApplicator;
    char _centerApplicator;
    char _leftApplicator;
    string _newId;
    char _dose;

public:
    RequestModel(RequestDto requestDto);
    RequestModel() {}

    string getNewId();
    char getDose();
    char getRequestType();
    char getRightApplicator();
    char getCenterApplicator();
    char getLeftApplicator();
};

#endif // REQUEST_MODEL_H