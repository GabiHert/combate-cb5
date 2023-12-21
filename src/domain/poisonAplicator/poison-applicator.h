#ifndef POISON_APPLICATOR_H
#define POISON_APPLICATOR_H
#include <Arduino.h>
#include "infra/system/system-interface.h"

class PoisonApplicator
{
private:
    unsigned char _motorPort, _sensorPort, _connectionSensorPort;
    ISystem *_sys;

public:
    PoisonApplicator();
    PoisonApplicator(ISystem *sys, unsigned char motorPortA, unsigned char sensorPort, unsigned char connectionSensorPort);

    unsigned char getMotorPort();
    unsigned char getSensorPort();

    void spin();
    void stop();
    bool readSensor();
    bool isConnected();
};

#endif