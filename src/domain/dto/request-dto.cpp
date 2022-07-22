#include <Arduino.h>
#include "domain/dto/request-dto.h"

RequestDto::RequestDto(String request)
{
    this->alarmSiren_ = request[3];
    this->dose_ = request[4];
    this->whellBoltsCounter_ = request[5];
};

char RequestDto::alarmSiren()
{
    return this->alarmSiren_;
};

char RequestDto::dose()
{
    return this->dose_;
};

char RequestDto::whellBoltsCounter()
{
    return this->whellBoltsCounter_;
};