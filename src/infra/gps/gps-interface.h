
#ifndef IGPS_H
#define IGPS_H
#include "infra/lcd/lcd-interface.h"
#include <string>
#include "types/error-or-string.h"
#include "types/error-or-boolean.h"
#include "utils/utils.h"
#include "config/config.h"
using namespace std;
class IGps
{
private:
    ILcd *_lcd;
    Timer *timer;
    ErrorOrString _getData(Timer *timer);

public:
    IGps(){};
    IGps(ILcd *lcd, Timer *timer);
    GprmcProtocolValidation gprmcProtocolValidation;
    ErrorOrString getData(int timeOut = CONFIG_GPS_TIMEOUT);
    ErrorOrBool setup();
};

#endif // IGPS_H