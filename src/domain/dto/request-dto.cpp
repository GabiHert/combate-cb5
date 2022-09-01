#include <Arduino.h>
#include "domain/dto/request-dto.h"
#include "utils/utils.h"
#include "config/config.h"

RequestDto::RequestDto(String request)
{
    this->_alarmSiren = request[3];
    this->_dose = request[4]; // FLAG: first time dose is initialized
    loggerInfo("RequestDto - constructor", "first time dose is initialized", "initializedDose: " + String(this->_dose) + " receivedDose: " + request[4]);
    this->_whellBoltsCounter = request[5];
};

char RequestDto::getAlarmSiren()
{
    return this->_alarmSiren;
};

char RequestDto::getDose()
{
    return this->_dose;
};

char RequestDto::getWhellBoltsCounter()
{
    return this->_whellBoltsCounter;
}