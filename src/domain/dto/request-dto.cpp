#include <Arduino.h>
#include "domain/dto/request-dto.h"
#include "utils/utils.h"
#include "config/config.h"
#include <string.h>
using namespace std;

RequestDto::RequestDto(string request)
{
    this->_requestType = request[4];
    this->_dose = request[5];
    this->_leftApplicator = request[6];
    this->_centerApplicator = request[7];
    this->_rightApplicator = request[8];
    this->_newId = request[9];
};
char RequestDto::getDose()
{
    return this->_dose;
};
char RequestDto::getNewId()
{
    return this->_newId;
}
char RequestDto::getRequestType()
{
    return this->_requestType;
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