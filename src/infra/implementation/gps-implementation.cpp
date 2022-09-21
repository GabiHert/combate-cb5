#include "interfaces/gps-interface.h"
#include <SoftwareSerial.h>
#include "utils/utils.h"
#include "config/config.h"
#include <string.h>
using namespace std;
SoftwareSerial gpsSerial(CONFIG().PORT_GPS_RX, CONFIG().PORT_GPS_TX);

string IGps::getData()
{

    loggerInfo("IGps.setLocation", "Process started");
    if (true) // gpsSerial.available()
    {
        string data = "001220.00,A,3001.89425,S,05109.81024,W,0.374,,240719,,,A*75"; // TODO: gpsSerial.readstring();

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
