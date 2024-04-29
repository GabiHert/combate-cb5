

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
#include "utils/utils.h"

class Cb
{
private:
    ISystem *_sys;
    App *_app;
    RequestModel requestModel;
    vector<PoisonApplicator *> _poisonApplicators;
    ILcd *_lcd;
    string _location;
    Timer* _timer;

    void _startApplicatorsSpin(bool * applicatorsToDose);

public:
    string id;

    Cb(App *app, ISystem *sys, ILcd *lcd,Timer *timer);
    Cb();

    pair<bool, ERROR_TYPE *> dose(char amount, bool *applicatorsToDose);

    void setRequestModel(RequestModel requestModel);
    RequestModel getRequestModel();
    vector<PoisonApplicator *> getPoisonApplicators();
};
#endif // CB_H