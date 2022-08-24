#include <Arduino.h>
#include "domain/cb/cb.h"
#include "utils/utils.h"
#include "config/config.h"

void Cb::dose()
{
    loggerInfo("Cb.dose", "Process started");
    // TODO: dose process
    loggerInfo("Cb.dose", "Process finished");
};
String Cb::getId()
{
    return this->_id;
};

char Cb::getWhellBoltsCountDecimal()
{
    return this->_wheelBoltsCount[0];
};
char Cb::getWhellBoltsCountUnit()
{
    return this->_wheelBoltsCount[1];
};

void Cb::clearWhellBoltsCount()
{
    this->_wheelBoltsCount[0] = '0';
    this->_wheelBoltsCount[1] = '0';
};

void Cb::addWhellBoltsCount()
{
    // TODO: Implemetar logica
    //  add somente ate 99
}

void Cb::setRequestModel(RequestModel requestModel)
{
    this->requestModel = requestModel;
};

RequestModel Cb::getRequestModel()
{
    return this->requestModel;
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
