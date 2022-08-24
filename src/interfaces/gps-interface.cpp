#include "interfaces/gps-interface.h"

void IGps::setLocation()
{
    this->gps.setLocation();
};

String IGps::getLocation(){
    return this->gps.getLocation();
}

void IGps::setupGps()
{
    this->gps.setupGps();
};