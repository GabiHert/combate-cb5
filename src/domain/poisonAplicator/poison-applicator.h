#ifndef POISON_APPLICATOR_H
#define POISON_APPLICATOR_H
#include <Arduino.h>

class PoisonApplicator
{
private:
    unsigned char motorPortA, motorPortB, sensorPort;

public:
    PoisonApplicator(){};
    PoisonApplicator(unsigned char motorPortA, unsigned char motorPortB, unsigned char sensorPort);
    void spin(unsigned char direction);
    bool readSensor();
};

#endif