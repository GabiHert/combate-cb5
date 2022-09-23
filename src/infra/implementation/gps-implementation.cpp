#include "interfaces/gps-interface.h"
#include <SoftwareSerial.h>
#include "utils/utils.h"
#include "config/config.h"
#include <string.h>
#include "exceptions/exceptions.h"
using namespace std;
SoftwareSerial gpsSerial(CONFIG().PORT_GPS_RX, CONFIG().PORT_GPS_TX);

ErrorOrString IGps::getData()
{
    loggerInfo("IGps.setLocation", "Process started");

    Timer timer;

    timer.setTimer(CONFIG().GPS_DATA_TIMEOUT);

    string data;
    int gpsData;

    while (gpsData != CONFIG().PROTOCOL_LF)
    {
        if (timer.timedOut())
        {
            loggerError("IGps.setLocation", "Process error", "Gps timed out");
            return ErrorOrString(EXCEPTIONS().GPS_TIME_OUT);
        }

        if (gpsSerial.available() > 0)
        {
            gpsData = gpsSerial.read();
            if (gpsData != CONFIG().PROTOCOL_LF && gpsData != CONFIG().PROTOCOL_CR)
                data += gpsData;
        }
    }

    loggerInfo("IGps.setLocation", "Process finished", " data: " + data);

    return ErrorOrString(data);
};

void IGps::setup()
{
    gpsSerial.begin(CONFIG().GPS_SERIAL_BOUD_RATE);
};
