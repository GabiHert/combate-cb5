#ifndef ERROR_TYPE_H
#define ERROR_TYPE_H
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

class ERROR_TYPE
{
public:
    string description;
    char errorCode[3];
    ERROR_TYPE(){};
    ERROR_TYPE(string description, char *errorCode)
    {
        strncpy(this->errorCode, errorCode, 3);
        this->description = description;
    };
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
    ERROR_TYPE *RENAME_ERROR;
    ERROR_TYPE ERROR_TYPES_ARRAY[ERROR_TYPE_MAPPED_ERRORS_AMOUNT];
};

#endif
