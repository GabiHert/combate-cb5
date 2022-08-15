
#ifndef IGPS_H
#define IGPS_H
#include "infra/implementation/gps-neo-6m-implementation.h"
#include <Arduino.h>

class IGps
{
private:
    GpsNeo6M gps;

public:
    String data;
    String getLocation();
    void setupGps();
};

#endif // IGPS_H