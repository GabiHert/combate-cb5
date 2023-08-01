

#ifndef CB_H
#define CB_H

#include "domain/model/request-model.h"
#include "infra/lcd/lcd-interface.h"
#include "domain/poisonAplicator/poison-applicator.h"
#include "config/config.h"
#include "infra/server/app.h"
#include "infra/system/system-interface.h"
#include <iostream>
#include "exceptions/error-type.h"
#include <vector>
class Cb
{
private:
    ISystem *_sys;
    App *_app;
    RequestModel requestModel;
    vector<PoisonApplicator *> _poisonApplicators;
    ILcd *_lcd;
    string _location;

public:
    char status;
    string id;

    Cb(App *app, ISystem *sys, ILcd *lcd);
    Cb();

    pair<bool, ERROR_TYPE *> dose(char amount, vector<bool> applicatorsToDose);

    void setRequestModel(RequestModel requestModel);
    RequestModel getRequestModel();
    vector<PoisonApplicator *> getPoisonApplicators();
    string getLocation() { return this->_location; };
    void setLocation(string location) { this->_location = location; };
};
#endif // CB_H