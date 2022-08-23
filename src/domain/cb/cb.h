

#ifndef CB_H
#define CB_H

#include "interfaces/gps-interface.h"
#include "interfaces/lcd-interface.h"
#include "domain/model/request-model.h"

class Cb
{
private:
    String _id;
    RequestModel requestModel;
    char _wheelBoltsCount[2];

public:
    IDisplay display;
    IGps gps;

    Cb(String id);
    Cb();

    void setup();
    void dose();

    String getId();

    void setRequestModel(RequestModel requestModel);
    RequestModel getRequestModel();

    char getWhellBoltsCountDecimal();
    char getWhellBoltsCountUnit();
    void addWhellBoltsCount();
    void clearWhellBoltsCount();
};
#endif // CB_H