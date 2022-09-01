#include <Arduino.h>
#include "domain/model/request-model.h"
#include "utils/utils.h"

RequestModel::RequestModel(RequestDto requestDto)
{
    this->_alarmSiren = requestDto.getAlarmSiren();
    this->_dose = requestDto.getDose(); // FLAG: second time dose is initialized
    loggerInfo("RequestModel - constructor", "first time dose is initialized", "initializedDose: " + String(this->_dose) + " receivedDose: " + requestDto.getDose());
    this->_whellBoltsCounter = requestDto.getWhellBoltsCounter();
};

char RequestModel::getAlarmSiren()
{
    return this->_alarmSiren;
};

char RequestModel::getDose()
{
    return this->_dose;
};

char RequestModel::getWhellBoltsCounter()
{
    return this->_whellBoltsCounter;
};