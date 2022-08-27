#ifndef POISON_APPLICATOR_H
#define POISON_APPLICATOR_H
#include <Arduino.h>
#include <interfaces/system-interface.h>


class PoisonApplicator
{
private:
    unsigned char motorPortA, motorPortB, sensorPort;
    ISystem sys;

public:
    PoisonApplicator(){};
    PoisonApplicator(unsigned char motorPortA, unsigned char motorPortB, unsigned char sensorPort);
    void calibrate();
    void spin(unsigned char direction);
    void stop();
    bool readSensor();
};

#endif