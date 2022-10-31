#include "domain/poisonAplicator/poison-applicator.h"
#include "utils/utils.h"
#include "config/config.h"
#include <Arduino.h>
#include <string.h>
using namespace std;

PoisonApplicator::PoisonApplicator(ISystem *sys, unsigned char motorPort, unsigned char _sensorPort)
{
    this->_sys = sys;
    this->_motorPort = motorPort;
    this->_sensorPort = _sensorPort;

    this->_sys->setupPort(this->_motorPort, OUTPUT);
    this->_sys->setupPort(this->_sensorPort, INPUT);
}

PoisonApplicator::PoisonApplicator()
{
}

void PoisonApplicator::calibrate()
{
    loggerInfo("PoisonApplicator.calibrate", "Process started", "motorPort: " + to_string(this->_motorPort));
    while (this->readSensor())
    {
        this->spin();
    }
    this->stop();
    loggerInfo("PoisonApplicator.calibrate", "Process started");
}

void PoisonApplicator::spin()
{

    loggerInfo("PoisonApplicator.spin", "Process started, _motorPort: " + to_string(this->_motorPort));

    this->_sys->setPort(this->_motorPort, HIGH);
    loggerInfo("PoisonApplicator.readSensor", "Process finished", " _motorPort: HIGH");
};

bool PoisonApplicator::readSensor()
{
    loggerInfo("PoisonApplicator.readSensor", "Process started");
    bool result = this->_sys->readDigitalPort(this->_sensorPort) ? true : false;
    loggerInfo("PoisonApplicator.readSensor", "Process finished", " result: " + to_string(result));
    return result;
};

void PoisonApplicator::stop()
{

    loggerInfo("PoisonApplicator.stop", "Process started", "_motorPort: " + to_string(this->_motorPort));
    this->_sys->setPort(this->_motorPort, 0);
    loggerInfo("PoisonApplicator.stop", "Process finished");
}

unsigned char PoisonApplicator::getMotorPort() { return this->_motorPort; }
unsigned char PoisonApplicator::getSensorPort() { return this->_sensorPort; }
