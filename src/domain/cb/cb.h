

#ifndef CB_H
#define CB_H

#include "domain/model/request-model.h"
#include "domain/poisonAplicator/poison-applicator.h"
#include "config/config.h"
#include "infra/server/app.h"
#include "interfaces/system-interface.h"
#include "types/error-or-boolean.h"
#include "types/error-or-int.h"

class Cb
{
private:
    ISystem *_sys;
    App *_app;
    string _id;
    string _status;
    RequestModel requestModel;
    PoisonApplicator _poisonApplicator[CONFIG_POISON_APPLICATORS];
    char _wheelBoltsCount[2];
    string _location;
    ErrorOrInt _connectedApplicators;

public:
    Cb(App *app, ISystem *sys);
    Cb();

    ErrorOrBool dose(char amount);
    string getId();
    string getStatus();

    void setRequestModel(RequestModel requestModel);
    RequestModel getRequestModel();

    PoisonApplicator *getPoisonApplicator();

    string getLocation() { return this->_location; };
    void setLocation(string location) { this->_location = location; };

    char getWhellBoltsCountDecimal();
    char getWhellBoltsCountUnit();
    ErrorOrInt getConnectedApplicators();

    void addWhellBoltsCount();
    void clearWhellBoltsCount();

    ErrorOrInt updateConnectedApplicators();
};
#endif // CB_H