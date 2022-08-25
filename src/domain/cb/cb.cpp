#include <Arduino.h>
#include "domain/cb/cb.h"
#include "utils/utils.h"
#include "config/config.h"

void Cb::dose()
{
    loggerInfo("Cb.dose", "Process started");
    do
    { // TODO:CONFERIR
        this->poisonApplicator[0].spin(CONFIG().SPIN_DIRECTION_CLOCKWISE);

    } while (!this->poisonApplicator[0].readSensor());

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
    this->_wheelBoltsCount[0] = '0';
    this->_wheelBoltsCount[1] = '0';
};

Cb::Cb()
{
    this->_wheelBoltsCount[0] = '0';
    this->_wheelBoltsCount[1] = '0';
}

void Cb::setup()
{

    this->display.setupDisplay();
    this->gps.setupGps();
    PoisonApplicator poisonApplicator_1(CONFIG().PORT_MOTOR_A_1, CONFIG().PORT_MOTOR_B_1, CONFIG().PORT_SENSOR_APPLICATOR_1);
    this->poisonApplicator[0] = poisonApplicator_1;
};
