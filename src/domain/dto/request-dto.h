
#ifndef REQUEST_DTO_H
#define REQUEST_DTO_H
#include <string.h>
#include <vector>
using namespace std;

class RequestDto
{
private:
    char _dose;
    char _requestType;
    string _name;
    vector<bool> _applicators;

public:
    RequestDto(string request);
    RequestDto(){};

    char getDose();

    char getRequestType();

    string getName();

    vector<bool> getApplicators();
};

#endif // REQUEST_DTO_H