#include "exceptions/error-type.h"

ERROR_TYPES::ERROR_TYPES()
{
    VALIDATION_ERROR = new ERROR_TYPE("ERR REQ INVALIDO", "001");
    DOSE_PROCESS_TIME_OUT = new ERROR_TYPE("ERR DOSE TIMEOUT", "002");
    GPS_TIME_OUT = new ERROR_TYPE("ERR GPS TIMEOUT", "003");
    PARSE_ERROR = new ERROR_TYPE("ERR PARSE", "004");
    NO_APPLICATORS_FOUND_ERROR = new ERROR_TYPE("ERR CON. DOSADOR", "005");
    this->ERROR_TYPES_ARRAY[0] = ERROR_TYPE("ERR REQ INVALIDO", "001");
    this->ERROR_TYPES_ARRAY[1] = ERROR_TYPE("ERR DOSE TIMEOUT", "002");
    this->ERROR_TYPES_ARRAY[2] = ERROR_TYPE("ERR GPS TIMEOUT", "003");
    this->ERROR_TYPES_ARRAY[3] = ERROR_TYPE("ERR PARSE", "004");
    this->ERROR_TYPES_ARRAY[4] = ERROR_TYPE("ERR CON. DOSADOR", "005");
};
