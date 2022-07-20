#include "infra/implementation/gps-neo-6m-implementation.h"

#ifndef IGPS_H
#define IGPS_H

class IGps
{
private:
    GpsNeo6M gps;

public:
    String getLocation();
    void setupGps();
};

#endif // IGPS_H