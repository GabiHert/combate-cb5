
#ifndef IGPS_H
#define IGPS_H
#include <string>
#include "types/error-or-string.h"
#include "types/error-or-boolean.h"
#include "config/config.h"
using namespace std;
class IGps
{
public:
    IGps(){};
    ErrorOrString getData(int timeOut = CONFIG().GPS_TIMEOUT);
    ErrorOrBool setup();
};

#endif // IGPS_H