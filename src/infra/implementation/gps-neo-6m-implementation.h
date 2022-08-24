#include <Arduino.h>

#ifndef GPS_NEO_6M_H
#define GPS_NEO_6M_H

class GpsNeo6M
{
    private:
    String location;
public:
    GpsNeo6M();
    void setLocation(); 
    String getLocation();
    void setupGps();
};

#endif //  GPS_NEO_6M_H