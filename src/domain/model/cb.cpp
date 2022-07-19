#include <Arduino.h>
#include "domain/model/model.h"
#include "utils/utils.h"
#include "config/config.h"

void Cb::dose(int amount)
{
    loggerInfo("Cb.dose", "Process started");
    // todo: dose process
    loggerInfo("Cb.dose", "Process finished");
};
String Cb::getId()
{
    loggerInfo("Cb.getId", "Process started");
    loggerInfo("Cb.getId", "Process finished");
    return this->id;
};

Cb::Cb(String id)
{
    this->id = id;
};
Cb::~Cb(){

};

void Cb::setup()
{
    this->display.setupDisplay();
    this->gps.setupGps();
};