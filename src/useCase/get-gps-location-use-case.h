#ifndef GET_GPS_LOCATION_USE_CASE_H
#define GET_GPS_LOCATION_USE_CASE_H
#include "interfaces/gps-interface.h"
#include "types/error-or-string.h"
#include "domain/cb/cb.h"
#include "interfaces/lcd-interface.h"

class GetGpsLocationUseCase
{

private:
    IGps *gps;
    IDisplay *display;
    Cb *cb;

public:
    GetGpsLocationUseCase() {}
    GetGpsLocationUseCase(IGps *gps, Cb *cb, IDisplay *display);
    ErrorOrString execute();
};

#endif