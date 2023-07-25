#ifndef ERROR_TYPE_H
#define ERROR_TYPE_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class ERROR_TYPE
{
public:
    string description;
    string errorCode;
    ERROR_TYPE(){};
    ERROR_TYPE(string _description, string _errorCode) : description(_description), errorCode(_errorCode){};
};

#define ERROR_TYPE_MAPPED_ERRORS_AMOUNT 6

class ERROR_TYPES
{
public:
    ERROR_TYPES();
    ERROR_TYPE *VALIDATION_ERROR;
    ERROR_TYPE *DOSE_PROCESS_TIME_OUT;
    ERROR_TYPE *GPS_TIME_OUT;
    ERROR_TYPE *PARSE_ERROR;
    ERROR_TYPE *NO_APPLICATORS_FOUND_ERROR;
    ERROR_TYPE ERROR_TYPES_ARRAY[ERROR_TYPE_MAPPED_ERRORS_AMOUNT];
};

#endif
