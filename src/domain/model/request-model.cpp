#include <Arduino.h>
#include "domain/model/request-model.h"
#include "utils/utils.h"

RequestModel::RequestModel(RequestDto requestDto)
{
    this->_requestType = requestDto.getRequestType();
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
string RequestModel::getNewId()
{
    return this->_newId;
}
char RequestModel::getRequestType()
{
    return this->_requestType;
}
char RequestModel::getRightApplicator()
{
    return this->_rightApplicator;
}
char RequestModel::getCenterApplicator()
{
    return this->_centerApplicator;
}
char RequestModel::getLeftApplicator()
{
    return this->_leftApplicator;
}