#include "interfaces/interfaces.h"

String IGps::getLocation()
{
    return this->gps.getLocation();
};

void IGps::setupGps()
{
    this->gps.setupGps();
};