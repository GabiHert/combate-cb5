#include "interfaces/gps-interface.h"
#include <SoftwareSerial.h>
#include "utils/utils.h"
#include "config/config.h"
#include "exceptions/error.h"
#include <string.h>
using namespace std;
SoftwareSerial gpsSerial(CONFIG().PORT_GPS_RX, CONFIG().PORT_GPS_TX);

string IGps::getData()
{

    loggerInfo("IGps.setLocation", "Process started");
    if (true) // gpsSerial.available()
    {
        string data = "$GPRMC,144326.00,A,5107.0017737,N,11402.3291611,W,0.080,323.3,210307,0.0,E,A*20"; // TODO: gpsSerial.readstring();

        loggerInfo("IGps.setLocation", "Process finished", " data: " + data);
        return data;
    }

    loggerInfo("IGps.setLocation", "Process finished", " No gps data available");
    return "";
};

void IGps::setup()
{
    gpsSerial.begin(CONFIG().SERIAL_BOUD_RATE);
};
