#include "interfaces/gps-interface.h"
#include <SoftwareSerial.h>
#include "utils/utils.h"
#include "config/config.h"
#include <string.h>
#include "exceptions/exceptions.h"
using namespace std;
SoftwareSerial gpsSerial(CONFIG_PORT_GPIO_GPS_RX, CONFIG_PORT_GPIO_GPS_TX);

ErrorOrString IGps::getData(int timeOut)
{
    loggerInfo("IGps.getData", "Process started");

    Timer timer;

    timer.setTimer(timeOut);

    string data = "";
    string header = "$GPRMC";
    char i = 0;
    int gpsData;
    bool dataTransferStarted = false;

    while (gpsData != CONFIG_PROTOCOL_LF || !dataTransferStarted)
    {
        if (timer.timedOut())
        {
            loggerError("IGps.getData", "Process error", "Gps timed out");
            return ErrorOrString(EXCEPTIONS().GPS_TIME_OUT);
        }

        if (gpsSerial.available() > 0)
        {

            gpsData = gpsSerial.read();

            if (gpsData == '$' && dataTransferStarted)
            {
                loggerWarn("IGps.getData", "Process warn", "data reset");

                i = 0;
                dataTransferStarted = false;
                data = "";
            }

            if (!dataTransferStarted)
            {
                if (gpsData == header[i])
                {
                    i++;
                    if (i == header.length())
                    {
                        dataTransferStarted = true;
                        data = header;
                    }
                }
                else
                {
                    loggerWarn("IGps.getData", "Process warn", "data reset " + gpsData);

                    i = 0;
                    dataTransferStarted = false;
                    data = "";
                }
            }
            else if (dataTransferStarted)
            {

                if (gpsData != CONFIG_PROTOCOL_LF && gpsData != CONFIG_PROTOCOL_CR)
                {

                    data += gpsData;
                }
            }
        }
    }

    loggerInfo("IGps.getData", "Process finished", data);

    return ErrorOrString(data);
};

ErrorOrBool IGps::setup()
{
    gpsSerial.begin(CONFIG_GPS_SERIAL_BOUD_RATE);
    // return ErrorOrBool(true);
    ErrorOrString errorOrString = this->getData(CONFIG_GPS_SETUP_TIMEOUT);
    if (errorOrString.isError())
    {
        return ErrorOrBool(EXCEPTIONS().GPS_TIME_OUT);
    }

    return ErrorOrBool(true);
};
