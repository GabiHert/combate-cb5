#include <Arduino.h>

#ifndef GPS_NEO_6M_H
#define GPS_NEO_6M_H

class GpsNeo6M
{
public:
    GpsNeo6M();
    String getLocation();
    void setupGps();
};

#endif //  GPS_NEO_6M_H