#include <Arduino.h>

#ifndef REQUEST_DTO_H
#define REQUEST_DTO_H

class RequestDto
{
private:
    char _alarmSiren;
    char _dose;
    char _whellBoltsCounter;
    bool validate(String request);

public:
    RequestDto(String request);

    char getAlarmSiren();
    char getDose();
    char getWhellBoltsCounter();
};

#endif // REQUEST_DTO_H