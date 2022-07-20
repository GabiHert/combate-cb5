#include "infra/implementation/gps-neo-6m-implementation.h"
#include <SoftwareSerial.h>
#include "config/config.h"
#include "utils/utils.h"

SoftwareSerial gpsSerial(CONFIG().GPS_RX, CONFIG().GPS_TX);

String GpsNeo6M::getLocation()
{
    loggerInfo("GpsNeo6M.getLocation", "Process started");
    if (gpsSerial.available())
    {
        String location = gpsSerial.readString();
        loggerInfo("GpsNeo6M.getLocation", "Process finished", " location: " + location);
        return location;
    };
    return "";
};
void GpsNeo6M::setupGps()
{
    loggerInfo("GpsNeo6M.setupGps", "Process started");

    gpsSerial.begin(CONFIG().SERIAL_BOUD_RATE);

    loggerInfo("GpsNeo6M.setupGps", "Process finished");
};
GpsNeo6M::GpsNeo6M(){};