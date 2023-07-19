#include <Arduino.h>
#include "domain/dto/request-dto.h"
#include "utils/utils.h"
#include "config/config.h"
#include <string.h>
using namespace std;

RequestDto::RequestDto(string request)
{
    this->_requestType = request[4];
    switch (this->_requestType)
    {
    case CONFIG_PROTOCOL_DOSE_REQUEST_TYPE:
        this->_dose = request[5];
        this->_applicators.push_back(request[6] == '1');
        this->_applicators.push_back(request[7] == '1');
        this->_applicators.push_back(request[8] == '1');
        break;

    case CONFIG_PROTOCOL_RENAME_REQUEST_TYPE:
        this->_name = request.substr(5, 8);
        break;
    }
};

char RequestDto::getDose()
{
    return this->_dose;
};

char RequestDto::getRequestType()
{
    return this->_requestType;
};

vector<bool> RequestDto::getApplicators()
{
    return this->_applicators;
};

string RequestDto::getName()
{
    return this->_name;
};