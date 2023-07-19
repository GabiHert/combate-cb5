
#ifndef REQUEST_MODEL_H
#define REQUEST_MODEL_H
#include <Arduino.h>
#include "domain/dto/request-dto.h"

class RequestModel
{
private:
    char _dose;
    char _requestType;
    string _name;
    vector<bool> _applicators;

public:
    RequestModel(RequestDto requestDto);
    RequestModel() {}

    char getDose();

    char getRequestType();

    string getName();

    vector<bool> getConnectedApplicators();
};

#endif // REQUEST_MODEL_H