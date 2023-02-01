
#ifndef IGPS_H
#define IGPS_H
#include <string>
#include "types/error-or-string.h"
#include "types/error-or-boolean.h"
#include "utils/utils.h"
#include "config/config.h"
using namespace std;
class IGps
{
private:
        ErrorOrString _getData(Timer *timer);

public:
    IGps(){};
    GprmcProtocolValidation gprmcProtocolValidation;
    ErrorOrString getData(int timeOut = CONFIG_GPS_TIMEOUT);
    ErrorOrBool setup();
};

#endif // IGPS_H