

#ifndef CB_H
#define CB_H

#include "interfaces/gps-interface.h"
#include "interfaces/lcd-interface.h"
#include "domain/model/request-model.h"
#include "domain/poisonAplicator/poison-applicator.h"
#include "config/config.h"
#include "infra/server/app.h"
#include "types/error-or-boolean.h"

class Cb
{
private:
    App *_app;
    string _id;
    string _status;
    RequestModel requestModel;
    PoisonApplicator _poisonApplicator[3];
    char _wheelBoltsCount[2];
    string _location;

public:
    IDisplay display;

    Cb(App *app);
    Cb();

    ErrorOrBool dose(int amount);
    void setup();

    string getId();
    string getStatus();

    void setRequestModel(RequestModel requestModel);
    RequestModel getRequestModel();
    PoisonApplicator *getPoisonApplicator();

    string getLocation() { return this->_location; };
    void setLocation(string location) { this->_location = location; };

    char getWhellBoltsCountDecimal();
    char getWhellBoltsCountUnit();
    void addWhellBoltsCount();
    void clearWhellBoltsCount();
};
#endif // CB_H