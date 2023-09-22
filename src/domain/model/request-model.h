
#ifndef REQUEST_MODEL_H
#define REQUEST_MODEL_H
#include <Arduino.h>
#include <string>
#include "domain/dto/request-dto.h"

class RequestModel
{
private:
    bool _rightApplicator;
    bool _centerApplicator;
    bool _leftApplicator;
    char _newId[2];
    char _dose;
    char _metersBetweenDose;

public:
    RequestModel(RequestDto requestDto);
    RequestModel() {}

    char *getNewId();
    char getDose();
    bool getRightApplicator();
    bool getCenterApplicator();
    bool getLeftApplicator();
    char getMetersBetweenDose();
};

#endif // REQUEST_MODEL_H