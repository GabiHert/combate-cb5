#ifndef GET_GPS_LOCATION_USE_CASE_H
#define GET_GPS_LOCATION_USE_CASE_H
#include "domain/cb/cb.h"

class GetGpsLocationUseCase
{

private:
    Cb *cb;

public:
    GetGpsLocationUseCase() {}
    GetGpsLocationUseCase(Cb *cb);
    void execute();
};

#endif