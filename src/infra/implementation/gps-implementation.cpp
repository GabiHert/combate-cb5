#include "interfaces/gps-interface.h"
#include <SoftwareSerial.h>
#include "utils/utils.h"
#include "config/config.h"

SoftwareSerial gpsSerial(CONFIG().PORT_GPS_RX, CONFIG().PORT_GPS_TX);

void IGps::setLocation()
{
    loggerInfo("IGps.setLocation", "Process started");
    if (true) // gpsSerial.available()
    {
        //  this->location = "$GPRMC,144326.00,A,5107.0017737,N,11402.3291611,W,0.080,323.3,210307,0.0,E,A*20"; // TODO: gpsSerial.readString();

        loggerInfo("IGps.setLocation", "Process finished", " location: " + this->location);
    }
    else
    {
        loggerInfo("IGps.setLocation", "Process finished", " No gps available");
    };
};

String IGps::getLocation()
{
    loggerInfo("IGps.getLocation", "Process started", "location: " + this->location);
    Serial.println(this->location);

    return this->location;
}

void IGps::setupGps()
{
    loggerInfo("IGps.setupGps", "Process started");

    gpsSerial.begin(CONFIG().SERIAL_BOUD_RATE);

    loggerInfo("IGps.setupGps", "Process finished");
};
