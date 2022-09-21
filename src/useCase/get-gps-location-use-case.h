#ifndef GET_GPS_LOCATION_USE_CASE_H
#define GET_GPS_LOCATION_USE_CASE_H
#include "interfaces/gps-interface.h"
#include "types/error-or-string.h"

class GetGpsLocationUseCase
{

private:
    IGps *gps;

public:
    GetGpsLocationUseCase() {}
    GetGpsLocationUseCase(IGps *gps);
    ErrorOrString execute();
};

#endif