#include <Arduino.h>
#include "domain/model/request-model.h"
#include "utils/utils.h"

RequestModel::RequestModel(RequestDto requestDto)
{
    this->_alarmSiren = requestDto.getAlarmSiren();
    this->_dose = requestDto.getDose();
};

char RequestModel::getAlarmSiren()
{
    return this->_alarmSiren;
};

char RequestModel::getDose()
{
    return this->_dose;
};
