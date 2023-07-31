
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
    char _newId[2];
    char _dose;

public:
    RequestDto(string request);
    RequestDto(){};
    string getNewId();
    char getDose();
    char getRequestType();
    char getRightApplicator();
    char getCenterApplicator();
    char getLeftApplicator();
};

#endif // REQUEST_DTO_H