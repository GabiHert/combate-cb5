#include <Arduino.h>
#include "domain/model/cb.h"
#include "utils/utils.h"
#include "config/config.h"

void Cb::dose(int amount)
{
    loggerInfo("Cb.dose", "Process started");
    // TODO: dose process
    loggerInfo("Cb.dose", "Process finished");
};
String Cb::id()
{
    return this->_id;
};

Cb::Cb(String id)
{
    this->_id = id;
};
Cb::Cb() {}
void Cb::setup()
{
    this->display.setupDisplay();
    this->gps.setupGps();
};
