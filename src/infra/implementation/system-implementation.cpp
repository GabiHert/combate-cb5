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
    return 1; // TODO:digitalRead(pin);
}

void ISystem::serialPrint(String message)
{
    Serial.print(message);
};

void ISystem::serialPrintln(String message)
{
    Serial.println(message);
};

String ISystem::serialRead()
{
    return Serial.readString();
};

int ISystem::serialAvailable()
{
    return Serial.available();
}