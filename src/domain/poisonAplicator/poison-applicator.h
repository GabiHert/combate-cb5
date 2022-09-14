#ifndef POISON_APPLICATOR_H
#define POISON_APPLICATOR_H
#include <Arduino.h>
#include <interfaces/system-interface.h>

class PoisonApplicator
{
private:
    int motorPortA, motorPortB, sensorPort;
    ISystem sys;

public:
    PoisonApplicator();
    PoisonApplicator(int motorPortA, int motorPortB, int sensorPort);

    int getMotorPortA();
    int getMotorPortB();
    int getSensorPort();

    void setup(int motorPortA, int motorPortB, int sensorPort);
    void calibrate();  
    void spin(int direction);
    void stop();
    bool readSensor();
};

#endif