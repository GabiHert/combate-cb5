#include <Arduino.h>
#include "domain/model/model.h"
#include "utils/utils.h"
#include "config/config.h"

boolean Cb::dose(int amount)
{
    loggerInfo("Cb.dose", "Process started");
    // todo: dose process
    loggerInfo("Cb.dose", "Process finished");
    return true;
};
String Cb::getId()
{
    loggerInfo("Cb.getId", "Process started");
    loggerInfo("Cb.getId", "Process finished");
    return this->id;
};
byte Cb::getLocation()
{
    loggerInfo("Cb.getLocation", "Process started");
    // todo: call gpsInterface
    loggerInfo("Cb.getLocation", "Process finished");
    return byte();
};

Cb::Cb(String id)
{
    this->id = id;
};
Cb::~Cb(){

};