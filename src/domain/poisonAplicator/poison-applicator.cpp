#include "domain/poisonAplicator/poison-applicator.h"
#include "utils/utils.h"
#include "config/config.h"

PoisonApplicator::PoisonApplicator(unsigned char motorPortA, unsigned char motorPortB, unsigned char sensorPort)
{

    this->sys.setPort(motorPortA, OUTPUT);
    this->sys.setPort(motorPortB, OUTPUT);
    this->sys.setPort(sensorPort, INPUT);

    this->motorPortA = motorPortA;
    this->motorPortB = motorPortB;
    this->sensorPort = sensorPort;
}

void PoisonApplicator::calibrate()
{
    loggerInfo("PoisonApplicator.calibrate", "Process started");
    while (this->readSensor())
    {
        this->spin(CONFIG().SPIN_DIRECTION_CLOCKWISE);
    }
    this->stop();
    loggerInfo("PoisonApplicator.calibrate", "Process started");
}

void PoisonApplicator::spin(unsigned char direction)
{
    loggerInfo("PoisonApplicator.spin", "Process started", "direction: " + String(direction));

    if (direction != (unsigned char)0 || direction != (unsigned char)1)
    {
        // TODO: throw error
    }

    if (direction)
    {
        this->sys.setPort(motorPortA, HIGH);
        this->sys.setPort(motorPortA, LOW);
        loggerInfo("PoisonApplicator.readSensor", "Process finished", " motorPortA: HIGH - motorPortB = LOW");
    }
    else
    {
        this->sys.setPort(motorPortA, LOW);
        this->sys.setPort(motorPortA, HIGH);
        loggerInfo("PoisonApplicator.readSensor", "Process finished", " motorPortA: LOW - motorPortB = HIGH");
    }
};

bool PoisonApplicator::readSensor()
{
    loggerInfo("PoisonApplicator.readSensor", "Process started");
    bool result = this->sys.readDigitalPort(this->sensorPort) ? true : false;
    loggerInfo("PoisonApplicator.readSensor", "Process finished", " result: " + String(result));
    return result;
};

void PoisonApplicator::stop()
{
    loggerInfo("PoisonApplicator.stop", "Process started");
    this->sys.setPort(motorPortA, LOW);
    this->sys.setPort(motorPortA, LOW);
    loggerInfo("PoisonApplicator.stop", "Process finished");
}
