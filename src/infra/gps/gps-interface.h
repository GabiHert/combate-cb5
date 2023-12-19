
#ifndef IGPS_H
#define IGPS_H
#include "infra/lcd/lcd-interface.h"
#include <string>
#include <iostream>
#include "utils/utils.h"
#include "config/config.h"
#include "exceptions/error-type.h"
#include "infra/validation/gprmc-protocol-validation.h"
using namespace std;
class IGps
{
private:
    ILcd *_lcd;
    Timer *_timer;
    pair<string, ERROR_TYPE *> _getData();

public:
    IGps(){};
    IGps(ILcd *lcd, Timer *timer);
    GprmcProtocolValidation gprmcProtocolValidation;
    pair<string, ERROR_TYPE *> getData(int timeOut = CONFIG_GPS_TIMEOUT);
    pair<bool, ERROR_TYPE *> setup();
};

#endif // IGPS_H