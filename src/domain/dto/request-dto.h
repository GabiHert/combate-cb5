
#ifndef REQUEST_DTO_H
#define REQUEST_DTO_H
#include <string.h>
using namespace std;

class RequestDto
{
private:
    char _alarmSiren;
    char _dose;
    char _wheelBoltsCounter;
    bool validate(string request);

public:
    RequestDto(string request);
    RequestDto(){};

    char getAlarmSiren();
    char getDose();
    char getWheelBoltsCounter();
};

#endif // REQUEST_DTO_H