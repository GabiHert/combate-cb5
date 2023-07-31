#include <Arduino.h>
#include "domain/dto/request-dto.h"
#include "utils/utils.h"
#include "config/config.h"
#include <string.h>
using namespace std;

RequestDto::RequestDto(string request)
{
    this->_dose = request[4];
};
char RequestDto::getDose()
{
    return this->_dose;
};
string RequestDto::getNewId()
{
    return to_string(this->_newId[0]) + to_string(this->_newId[1]);
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