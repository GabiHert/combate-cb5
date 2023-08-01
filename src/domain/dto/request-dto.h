
#ifndef REQUEST_DTO_H
#define REQUEST_DTO_H
#include <string.h>
using namespace std;

class RequestDto
{
private:
    char _requestType;
    char _rightApplicator;
    char _centerApplicator;
    char _leftApplicator;
    char _newId;
    char _dose;

public:
    RequestDto(string request);
    RequestDto(){};
    char getNewId();
    char getDose();
    char getRequestType();
    char getRightApplicator();
    char getCenterApplicator();
    char getLeftApplicator();
};

#endif // REQUEST_DTO_H