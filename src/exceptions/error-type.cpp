#include "exceptions/error-type.h"

ERROR_TYPES::ERROR_TYPES()
{
    char C001[3] = {'0', '0', '1'};
    char C002[3] = {'0', '0', '2'};
    char C003[3] = {'0', '0', '3'};
    char C004[3] = {'0', '0', '4'};
    char C009[3] = {'0', '0', '9'};
    char C010[3] = {'0', '1', '0'};

    VALIDATION_ERROR = new ERROR_TYPE("E. VALIDACAO", C001);
    DOSE_PROCESS_TIME_OUT = new ERROR_TYPE("E. DOSE LENTA", C002);
    GPS_TIME_OUT = new ERROR_TYPE("E. GPS LENTO", C003);
    PARSE_ERROR = new ERROR_TYPE("E. PARSE", C004);
    NO_APPLICATORS_FOUND_ERROR = new ERROR_TYPE("E. CON. DOSADOR", C009);
    RENAME_ERROR = new ERROR_TYPE("E. RENOMEAR", C010);
    DOSE_PROCESS_TOO_FAST = = new ERROR_TYPE("E. DOSE RAPIDA", C002);

    this->ERROR_TYPES_ARRAY[0] = *VALIDATION_ERROR;
    this->ERROR_TYPES_ARRAY[1] = *DOSE_PROCESS_TIME_OUT;
    this->ERROR_TYPES_ARRAY[2] = *GPS_TIME_OUT;
    this->ERROR_TYPES_ARRAY[3] = *PARSE_ERROR;
    this->ERROR_TYPES_ARRAY[4] = *NO_APPLICATORS_FOUND_ERROR;
    this->ERROR_TYPES_ARRAY[5] = *RENAME_ERROR;
    this->ERROR_TYPES_ARRAY[5] = *DOSE_PROCESS_TOO_FAST;
};
