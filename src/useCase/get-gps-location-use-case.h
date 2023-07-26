#ifndef GET_GPS_LOCATION_USE_CASE_H
#define GET_GPS_LOCATION_USE_CASE_H
#include "infra/gps/gps-interface.h"
#include "domain/cb/cb.h"
#include "infra/lcd/lcd-interface.h"
#include <iostream>

class GetGpsLocationUseCase
{

private:
    IGps *gps;
    ILcd *lcd;
    Cb *cb;

public:
    GetGpsLocationUseCase() {}
    GetGpsLocationUseCase(IGps *gps, Cb *cb, ILcd *lcd);
    pair<string, ERROR_TYPE *> execute();
};

#endif