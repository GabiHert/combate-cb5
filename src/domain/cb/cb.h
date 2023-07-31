

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
    string _id;
    string _status;
    RequestModel requestModel;
    vector<PoisonApplicator *> _poisonApplicators;
    ILcd *_lcd;
    string _location;
    pair<vector<bool>, ERROR_TYPE *> _applicators;
    pair<vector<bool>, ERROR_TYPE *> _connectedApplicators;

public:
    Cb(App *app, ISystem *sys, ILcd *lcd);
    Cb();

    pair<bool, ERROR_TYPE *> dose(char amount);
    string getId();
    string getStatus();
    unsigned char getConnectedApplicators();
    void setRequestModel(RequestModel requestModel);
    RequestModel getRequestModel();
    vector<PoisonApplicator *> getPoisonApplicators();
    string getLocation() { return this->_location; };
    void setLocation(string location) { this->_location = location; };
    void clearStatus();
};
#endif // CB_H