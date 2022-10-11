#include "interfaces/gps-interface.h"
#include <SoftwareSerial.h>
#include "utils/utils.h"
#include "config/config.h"
#include <string.h>
#include "exceptions/exceptions.h"
using namespace std;
SoftwareSerial gpsSerial(CONFIG().PORT_GPS_RX, CONFIG().PORT_GPS_TX);

ErrorOrString IGps::getData(int timeOut)
{
    loggerInfo("IGps.getData", "Process started");

    Timer timer;

    timer.setTimer(timeOut);

    string data;
    int gpsData;
    bool dataTransferStarted = false, dataTransferFinished = false, restartTransfer = false;

    while (gpsData != CONFIG().PROTOCOL_LF)
    {
        if (timer.timedOut())
        {
            loggerError("IGps.getData", "Process error", "Gps timed out");
            return ErrorOrString(EXCEPTIONS().GPS_TIME_OUT);
        }

        if (gpsSerial.available() > 0)
        {
            gpsData = gpsSerial.read();

            if (gpsData == '$')
            {
                if (!dataTransferStarted)
                {
                    dataTransferStarted = true;
                }
                else
                {
                    loggerWarn("IGps.getData", "Process warn", "reset");

                    dataTransferStarted = false;
                    if (gpsSerial.available() > 0)
                        data = "";
                }
            }

            if (dataTransferStarted)
            {
                if (gpsData != CONFIG().PROTOCOL_LF && gpsData != CONFIG().PROTOCOL_CR)
                {
                    data += gpsData;
                }
            }
        }
    }

    loggerInfo("IGps.getData", "Process finished", " data: " + data);

    return ErrorOrString(data);
};

ErrorOrBool IGps::setup()
{
    gpsSerial.begin(CONFIG().GPS_SERIAL_BOUD_RATE);
    // return ErrorOrBool(true);
    ErrorOrString errorOrString = this->getData(CONFIG().GPS_SETUP_TIMEOUT);
    if (errorOrString.isError())
    {
        return ErrorOrBool(EXCEPTIONS().GPS_TIME_OUT);
    }

    return ErrorOrBool(true);
};
