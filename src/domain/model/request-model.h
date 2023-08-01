
#ifndef REQUEST_MODEL_H
#define REQUEST_MODEL_H
#include <Arduino.h>
#include <string>
#include "domain/dto/request-dto.h"

class RequestModel
{
private:
    char _requestType;
    bool _rightApplicator;
    bool _centerApplicator;
    bool _leftApplicator;
    char _newId;
    char _dose;

public:
    RequestModel(RequestDto requestDto);
    RequestModel() {}

    char getNewId();
    char getDose();
    char getRequestType();
    bool getRightApplicator();
    bool getCenterApplicator();
    bool getLeftApplicator();
};

#endif // REQUEST_MODEL_H