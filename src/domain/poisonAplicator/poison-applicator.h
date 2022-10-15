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
    PoisonApplicator();
    PoisonApplicator(unsigned char motorPortA, unsigned char motorPortB, unsigned char sensorPort);

    unsigned char getMotorPortA();
    unsigned char getMotorPortB();
    unsigned char getSensorPort();

    void calibrate();
    void spin(int direction);
    void stop();
    bool readSensor();
};

#endif