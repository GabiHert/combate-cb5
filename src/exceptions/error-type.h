#ifndef ERROR_TYPE_H
#define ERROR_TYPE_H
#include <string>
using namespace std;

class ERROR_TYPE
{
public:
    string description;
    string errorCode;
    ERROR_TYPE(){};
    ERROR_TYPE(string _description, string _errorCode) : description(_description), errorCode(_errorCode){};
};

struct ERROR_CODE
{
    string VALIDATION_ERROR = "001", DOSE_PROCESS_TIME_OUT = "002", GPS_TIME_OUT = "003", PARSE_ERROR = "003";
};

#endif