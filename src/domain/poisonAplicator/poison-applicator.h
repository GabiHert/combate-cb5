#ifndef POISON_APPLICATOR_H
#define POISON_APPLICATOR_H
#include <Arduino.h>
#include "infra/system/system-interface.h"

class PoisonApplicator
{
private:
    unsigned char _motorPort, _sensorPort;
    ISystem *_sys;

public:
    PoisonApplicator();
    PoisonApplicator(ISystem *sys, unsigned char motorPortA, unsigned char sensorPort);

    unsigned char getMotorPort();
    unsigned char getSensorPort();

    void calibrate();
    void spin();
    void stop();
    bool readSensor();
};

#endif