#include "infra/implementation/gps-neo-6m-implementation.h"
#include <SoftwareSerial.h>
#include "config/config.h"
#include "utils/utils.h"

SoftwareSerial gpsSerial(CONFIG().GPS_RX, CONFIG().GPS_TX);

void GpsNeo6M::setLocation()
{
    loggerInfo("GpsNeo6M.getLocation", "Process started");
    if (gpsSerial.available())
    {
        String location = "$GPRMC,144326.00,A,5107.0017737,N,11402.3291611,W,0.080,323.3,210307,0.0,E,A*20"; // TODO: gpsSerial.readString();
        loggerInfo("GpsNeo6M.getLocation", "Process finished", " location: " + location);
        this->location = location;
    };
};
void GpsNeo6M::setupGps()
{
    loggerInfo("GpsNeo6M.setupGps", "Process started");

    gpsSerial.begin(CONFIG().SERIAL_BOUD_RATE);

    loggerInfo("GpsNeo6M.setupGps", "Process finished");
};

String GpsNeo6M::getLocation()
{
    return this->location;
};
GpsNeo6M::GpsNeo6M(){};