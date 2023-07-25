#include "infra/system/system-interface.h"
#include <Arduino.h>
#include <string.h>
#include "utils/utils.h"
#include "config/config.h"

using namespace std;
void ISystem::setPort(unsigned char pin, unsigned char state)
{
    digitalWrite(pin, state);
};

void ISystem::setupPort(unsigned char pin, unsigned char mode)
{
    pinMode(pin, mode);
};

bool ISystem::readDigitalPort(unsigned char pin)
{
    loggerInfo("ISystem.readDigitalPort", "Process started", "pin: " + to_string(pin));
    bool result = digitalRead(pin) > 0;
    loggerInfo("ISystem.readDigitalPort", "Process finished", "result: " + to_string(result));

    return result;
}

void ISystem::serialPrint(string message)
{
    Serial.print(stdStringToArduinoString(message));
};

void ISystem::serialPrintln(string message)
{
    Serial.println(stdStringToArduinoString(message));
};

string ISystem::serialRead()
{
    return arduinoStringToStdString(Serial.readString());
};

bool ISystem::serialAvailable()
{
    return Serial.available() > 0;
}

ISystem::ISystem()
{
    Serial.begin(CONFIG_SERIAL_BAUD_RATE);
}