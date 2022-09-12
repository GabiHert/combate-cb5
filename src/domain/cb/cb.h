

#ifndef CB_H
#define CB_H

#include "interfaces/gps-interface.h"
#include "interfaces/lcd-interface.h"
#include "domain/model/request-model.h"
#include "domain/poisonAplicator/poison-applicator.h"
#include "config/config.h"

class Cb
{
private:
    string _id;
    RequestModel requestModel;
    PoisonApplicator poisonApplicator[3];
    char _wheelBoltsCount[2];
    void setupApplicator();

public:
    IDisplay display;
    IGps gps;

    Cb(string id);
    Cb();

    void dose();
    void setup();
    string getId();

    void setRequestModel(RequestModel requestModel);
    RequestModel getRequestModel();
    PoisonApplicator *getPoisonApplicator();

    char getWhellBoltsCountDecimal();
    char getWhellBoltsCountUnit();
    void addWhellBoltsCount();
    void clearWhellBoltsCount();
};
#endif // CB_H