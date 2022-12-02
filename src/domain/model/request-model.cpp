#include <Arduino.h>
#include "domain/model/request-model.h"
#include "utils/utils.h"

RequestModel::RequestModel(RequestDto requestDto)
{
    this->_alarmSiren = requestDto.getAlarmSiren();
    this->_dose = requestDto.getDose();
    this->_wheelBoltsCounter = requestDto.getWheelBoltsCounter();
};

char RequestModel::getAlarmSiren()
{
    return this->_alarmSiren;
};

char RequestModel::getDose()
{
    return this->_dose;
};

char RequestModel::getWheelBoltsCounter()
{
    return this->_wheelBoltsCounter;
};