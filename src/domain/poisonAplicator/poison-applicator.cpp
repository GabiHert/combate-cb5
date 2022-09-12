#include "domain/poisonAplicator/poison-applicator.h"
#include "utils/utils.h"
#include "config/config.h"
#include <Arduino.h>
#include <string.h>
using namespace std;

PoisonApplicator::PoisonApplicator(int motorPortA, int motorPortB, int sensorPort)
{

    this->motorPortA = motorPortA;
    this->motorPortB = motorPortB;
    this->sensorPort = sensorPort;

    this->sys.setupPort(this->motorPortA, OUTPUT);
    this->sys.setupPort(this->motorPortB, OUTPUT);
    this->sys.setupPort(this->sensorPort, INPUT);
}

void PoisonApplicator::setup(int motorPortA, int motorPortB, int sensorPort)
{

    this->motorPortA = motorPortA;
    this->motorPortB = motorPortB;
    this->sensorPort = sensorPort;

    this->sys.setupPort(this->motorPortA, OUTPUT);
    this->sys.setupPort(this->motorPortB, OUTPUT);
    this->sys.setupPort(this->sensorPort, INPUT);
}

PoisonApplicator::PoisonApplicator()
{
    this->motorPortA = 0;
    this->motorPortB = 0;
    this->sensorPort = 0;
}

void PoisonApplicator::calibrate()
{
    loggerInfo("PoisonApplicator.calibrate", "Process started", "motorPortA: " + to_string(this->motorPortA) + " motorPortB: " + to_string(this->motorPortB));
    while (this->readSensor())
    {
        this->spin(CONFIG().SPIN_DIRECTION_CLOCKWISE);
    }
    this->stop();
    loggerInfo("PoisonApplicator.calibrate", "Process started");
}

void PoisonApplicator::spin(int direction)
{
    loggerInfo("PoisonApplicator.spin", "Process started", "direction: " + to_string(direction) + " motorPortA: " + to_string(this->motorPortA) + " motorPortB: " + to_string(this->motorPortB));

    if (direction != 0 || direction != 1)
    {
        // TODO: throw error
    }

    if (direction)
    {
        this->sys.setPort(this->motorPortA, 1);
        this->sys.setPort(this->motorPortB, 0);
        loggerInfo("PoisonApplicator.readSensor", "Process finished", " motorPortA: HIGH - motorPortB = LOW");
    }
    else
    {
        this->sys.setPort(this->motorPortA, 0);
        this->sys.setPort(this->motorPortB, 1);
        loggerInfo("PoisonApplicator.readSensor", "Process finished", " motorPortA: LOW - motorPortB = HIGH");
    }
};

bool PoisonApplicator::readSensor()
{
    loggerInfo("PoisonApplicator.readSensor", "Process started");
    bool result = this->sys.readDigitalPort(this->sensorPort) ? true : false;
    loggerInfo("PoisonApplicator.readSensor", "Process finished", " result: " + to_string(result));
    return result;
};

void PoisonApplicator::stop()
{
    loggerInfo("PoisonApplicator.stop", "Process started", "motorPortA: " + to_string(this->motorPortA) + " motorPortB: " + to_string(this->motorPortB));
    this->sys.setPort(this->motorPortA, 0);
    this->sys.setPort(this->motorPortB, 0);
    loggerInfo("PoisonApplicator.stop", "Process finished");
}

int PoisonApplicator::getMotorPortA() { return this->motorPortA; }
int PoisonApplicator::getMotorPortB() { return this->motorPortB; }
int PoisonApplicator::getSensorPort() { return this->sensorPort; }
