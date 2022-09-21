
#ifndef REQUEST_DTO_H
#define REQUEST_DTO_H
#include <string.h>
using namespace std;

class RequestDto
{
private:
    char _alarmSiren;
    char _dose;
    char _whellBoltsCounter;
    bool validate(string request);

public:
    RequestDto(string request);
    RequestDto(){};

    char getAlarmSiren();
    char getDose();
    char getWhellBoltsCounter();
};

#endif // REQUEST_DTO_H