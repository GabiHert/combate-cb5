
#ifndef REQUEST_MODEL_H
#define REQUEST_MODEL_H
#include <Arduino.h>
#include "domain/dto/request-dto.h"

class RequestModel
{
private:
    char _alarmSiren;
    char _dose;

public:
    RequestModel(RequestDto requestDto);
    RequestModel() {}

    char getAlarmSiren();
    char getDose();
};

#endif // REQUEST_MODEL_H