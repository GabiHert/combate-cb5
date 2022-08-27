
#ifndef IGPS_H
#define IGPS_H
#include <Arduino.h>

class IGps
{
private:
    String location;

public:
    IGps(){};
    String getLocation();
    void setLocation();
    void setupGps();
};

#endif // IGPS_H