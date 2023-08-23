#include "domain/poisonAplicator/poison-applicator.h"
#include "utils/utils.h"
#include "config/config.h"
#include <Arduino.h>
#include <string.h>
using namespace std;

PoisonApplicator::PoisonApplicator(ISystem *sys, unsigned char motorPort, unsigned char _sensorPort, unsigned char connectionSensorPort)
{
    this->_sys = sys;
    this->_motorPort = motorPort;
    this->_sensorPort = _sensorPort;
    this->_connectionSensorPort = connectionSensorPort;

    this->_sys->setupPort(this->_motorPort, OUTPUT);
    this->_sys->setupPort(this->_sensorPort, INPUT);
    this->stop();
}

PoisonApplicator::PoisonApplicator()
{
    this->stop();
}

void PoisonApplicator::calibrate()
{
    while (this->readSensor())
    {
        this->spin();
    }
    this->stop();
}

void PoisonApplicator::spin()
{
    this->_sys->setPort(this->_motorPort, HIGH);
};

bool PoisonApplicator::readSensor()
{
    bool result = this->_sys->readDigitalPort(this->_sensorPort) ? true : false;
    return result;
};

void PoisonApplicator::stop()
{
    this->_sys->setPort(this->_motorPort, LOW);
}

bool PoisonApplicator::isConnected()
{
    return !this->_sys->readDigitalPort(this->_connectionSensorPort);
}

unsigned char PoisonApplicator::getMotorPort() { return this->_motorPort; }
unsigned char PoisonApplicator::getSensorPort() { return this->_sensorPort; }
