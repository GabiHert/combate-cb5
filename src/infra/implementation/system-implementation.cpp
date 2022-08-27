#include "interfaces/system-interface.h"
#include <Arduino.h>

void ISystem::setPort(unsigned char pin, unsigned char state)
{
    digitalWrite(pin, state);
};

void ISystem::setupPort(unsigned char pin, unsigned char mode)
{
    pinMode(pin, mode);
};

int ISystem::readDigitalPort(unsigned char pin)
{
    return digitalRead(pin);
}