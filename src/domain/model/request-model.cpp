#include <Arduino.h>
#include "domain/model/request-model.h"
#include "utils/utils.h"

RequestModel::RequestModel(RequestDto requestDto)
{
    this->_name = requestDto.getName();
    this->_requestType = requestDto.getRequestType();
    this->_dose = requestDto.getDose();
    this->_applicators = requestDto.getApplicators();
};

vector<bool> RequestModel::getConnectedApplicators()
{
    return this->_applicators;
};

char RequestModel::getDose()
{
    return this->_dose;
};

char RequestModel::getRequestType()
{
    return this->_requestType;
};

string RequestModel::getName()
{
    return this->_name;
};