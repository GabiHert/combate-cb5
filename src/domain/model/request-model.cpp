#include <Arduino.h>
#include "domain/model/request-model.h"
#include "utils/utils.h"

RequestModel::RequestModel(RequestDto requestDto)
{
    this->_dose = requestDto.getDose();
    this->_leftApplicator = requestDto.getLeftApplicator();
    this->_centerApplicator = requestDto.getCenterApplicator();
    this->_rightApplicator = requestDto.getRightApplicator();
    this->_newId = requestDto.getNewId();
};
char RequestModel::getDose()
{
    return this->_dose;
};
char RequestModel::getNewId()
{
    return this->_newId;
}
bool RequestModel::getRightApplicator()
{
    return this->_rightApplicator;
}
bool RequestModel::getCenterApplicator()
{
    return this->_centerApplicator;
}
bool RequestModel::getLeftApplicator()
{
    return this->_leftApplicator;
}