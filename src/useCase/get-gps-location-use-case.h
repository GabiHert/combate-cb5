#ifndef GET_GPS_LOCATION_USE_CASE_H
#define GET_GPS_LOCATION_USE_CASE_H
#include "interfaces/gps-interface.h"
#include "types/error-or-string.h"
#include "domain/cb/cb.h"

class GetGpsLocationUseCase
{

private:
    IGps *gps;
    Cb *cb;

public:
    GetGpsLocationUseCase() {}
    GetGpsLocationUseCase(IGps *gps, Cb *cb);
    ErrorOrString execute();
};

#endif