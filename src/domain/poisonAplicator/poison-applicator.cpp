#include "domain/poisonAplicator/poison-applicator.h"
#include "utils/utils.h"

PoisonApplicator::PoisonApplicator(unsigned char motorPortA, unsigned char motorPortB, unsigned char sensorPort)
{
    pinMode(motorPortA, OUTPUT);
    pinMode(motorPortB, OUTPUT);
    pinMode(sensorPort, INPUT);
    this->motorPortA = motorPortA;
    this->motorPortB = motorPortB;
    this->sensorPort = sensorPort;
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
        digitalWrite(motorPortA, HIGH);
        digitalWrite(motorPortA, LOW);
        loggerInfo("PoisonApplicator.readSensor", "Process finished", " motorPortA: HIGH - motorPortB = LOW");
    }
    else
    {
        digitalWrite(motorPortA, LOW);
        digitalWrite(motorPortA, HIGH);
        loggerInfo("PoisonApplicator.readSensor", "Process finished", " motorPortA: LOW - motorPortB = HIGH");
    }
};

bool PoisonApplicator::readSensor()
{
    loggerInfo("PoisonApplicator.readSensor", "Process started");
    bool result = digitalRead(this->sensorPort) ? true : false;
    loggerInfo("PoisonApplicator.readSensor", "Process finished", " result: " + String(result));
    return result;
};
