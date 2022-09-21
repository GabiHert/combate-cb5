#ifndef ERROR_TYPE_H
#define ERROR_TYPE_H
#include <Arduino.h>

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
    string VALIDATION_ERROR = "001";
    string DOSE_PROCESS_TIME_OUT = "002";
};

#endif