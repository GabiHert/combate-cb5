#include <Arduino.h>
#include "domain/dto/request-dto.h"
#include "utils/utils.h"
#include "config/config.h"
#include <string.h>
using namespace std;

RequestDto::RequestDto(string request)
{
    this->_dose = request[4];
    this->_leftApplicator = request[5];
    this->_centerApplicator = request[6];
    this->_rightApplicator = request[7];
    this->_newId[0] = request[8];
    this->_newId[1] = request[9];
    this->_metersBetweenDose = request[10];
};
char RequestDto::getDose()
{
    return this->_dose;
};
char *RequestDto::getNewId()
{
    return this->_newId;
}
char RequestDto::getRightApplicator()
{
    return this->_rightApplicator;
}
char RequestDto::getCenterApplicator()
{
    return this->_centerApplicator;
}
char RequestDto::getLeftApplicator()
{
    return this->_leftApplicator;
}
char RequestDto::getMetersBetweenDose()
{
    return this->_metersBetweenDose;
}