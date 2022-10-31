#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include "error-type.h"
struct EXCEPTIONS
{
    ERROR_TYPE VALIDATION_ERROR = ERROR_TYPE("Invalid request", ERROR_CODE().VALIDATION_ERROR);
    ERROR_TYPE DOSE_PROCESS_TIME_OUT = ERROR_TYPE("Dose timed out", ERROR_CODE().DOSE_PROCESS_TIME_OUT);
    ERROR_TYPE GPS_TIME_OUT = ERROR_TYPE("GPS timed out", ERROR_CODE().GPS_TIME_OUT);
    ERROR_TYPE PARSE_ERROR = ERROR_TYPE("Error parsing types", ERROR_CODE().PARSE_ERROR);
    ERROR_TYPE NO_APPLICATORS_FOUND_ERROR = ERROR_TYPE("Error connecting to applicators", ERROR_CODE().NO_APPLICATORS_FOUND_ERROR);
};

#endif