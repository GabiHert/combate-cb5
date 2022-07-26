

#ifndef CB_H
#define CB_H

#include "domain/model/request-model.h"
#include "interfaces/lcd-interface.h"
#include "domain/poisonAplicator/poison-applicator.h"
#include "config/config.h"
#include "infra/server/app.h"
#include "interfaces/system-interface.h"
#include "types/error-or-boolean-vector.h"
#include "types/error-or-boolean.h"
#include "types/error-or-int.h"
#include <vector>
class Cb
{
private:
    ISystem *_sys;
    App *_app;
    string _id;
    string _status;
    RequestModel requestModel;
    vector<PoisonApplicator *> _poisonApplicators;
    IDisplay *_display;
    char _wheelBoltsCount[2];
    string _location;
    ErrorOrBoolVector _applicators;
    int _connectedApplicators;

public:
    Cb(App *app, ISystem *sys, IDisplay *display);
    Cb();

    ErrorOrBool dose(char amount);
    string getId();
    string getStatus();
    int getConnectedApplicators();
    void setRequestModel(RequestModel requestModel);
    RequestModel getRequestModel();
    vector<PoisonApplicator *>getPoisonApplicator();
    string getLocation() { return this->_location; };
    void setLocation(string location) { this->_location = location; };
    char getWheelBoltsCountDecimal();
    char getWheelBoltsCountUnit();
    ErrorOrBoolVector getApplicators();
    void addWheelBoltsCount();
    void clearWheelBoltsCount();
    ErrorOrInt updateConnectedApplicators();
};
#endif // CB_H