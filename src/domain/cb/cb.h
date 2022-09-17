

#ifndef CB_H
#define CB_H

#include "interfaces/gps-interface.h"
#include "interfaces/lcd-interface.h"
#include "domain/model/request-model.h"
#include "domain/poisonAplicator/poison-applicator.h"
#include "config/config.h"
#include "infra/server/app.h"

class Cb
{
private:
    IGps _gps;
    App *_app;
    string _id;
    string _status;
    RequestModel requestModel;
    PoisonApplicator _poisonApplicator[3];
    char _wheelBoltsCount[2];
    string _gpsData;
    void _setupApplicator();

public:
    IDisplay display;

    Cb(App *app);
    Cb();

    void dose(int amount);
    void setup();

    string getId();
    string getStatus();
    string getGpsData();

    void setRequestModel(RequestModel requestModel);
    RequestModel getRequestModel();
    PoisonApplicator *getPoisonApplicator();

    char getWhellBoltsCountDecimal();
    char getWhellBoltsCountUnit();
    void addWhellBoltsCount();
    void clearWhellBoltsCount();
};
#endif // CB_H