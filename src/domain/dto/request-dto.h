#include <Arduino.h>

#ifndef REQUEST_DTO_H
#define REQUEST_DTO_H

class RequestDto
{
private:
    char alarmSiren_;
    char dose_;
    char whellBoltsCounter_;

public:
    RequestDto(String request);

    char alarmSiren();
    char dose();
    char whellBoltsCounter();
};

#endif // REQUEST_DTO_H