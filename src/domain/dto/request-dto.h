
#ifndef REQUEST_DTO_H
#define REQUEST_DTO_H
#include <string.h>
using namespace std;

class RequestDto
{
private:
    char _rightApplicator;
    char _centerApplicator;
    char _leftApplicator;
    char _newId[2];
    char _dose;
    char _metersBetweenDose;

public:
    RequestDto(string request);
    RequestDto(){};
    char *getNewId();
    char getDose();
    char getRightApplicator();
    char getCenterApplicator();
    char getMetersBetweenDose();
    char getLeftApplicator();
};

#endif // REQUEST_DTO_H