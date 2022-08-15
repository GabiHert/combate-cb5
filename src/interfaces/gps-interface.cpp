#include "interfaces/gps-interface.h"

String IGps::getLocation()
{
    String location =  this->gps.getLocation();
    this->data = location;
    return location;
};

void IGps::setupGps()
{
    this->gps.setupGps();
};