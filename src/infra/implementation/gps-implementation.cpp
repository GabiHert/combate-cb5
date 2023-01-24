#include "interfaces/gps-interface.h"
#include <SoftwareSerial.h>
#include "utils/utils.h"
#include "config/config.h"
#include <Arduino.h>
#include <string.h>
#include "exceptions/exceptions.h"
using namespace std;
SoftwareSerial gpsSerial(CONFIG_PORT_GPIO_GPS_RX, CONFIG_PORT_GPIO_GPS_TX);

ErrorOrString IGps::_getData(Timer *timer)
{
    ErrorOrString errorOrString = ErrorOrString("$GPRMC,001220.00,A,3001.89425,S,05109.81024,W,0.374,,240719,,,N*75");
    return errorOrString;
    string data = "";
    char startHeaderCount = 0;
    int gpsData;
    bool dataTransferStarted = false;
    // todo: fazer o flush (limpar o buffer)

    while (gpsData != CONFIG_PROTOCOL_LF || !dataTransferStarted)
    {

        if (timer->timedOut())
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

                startHeaderCount = 0;
                dataTransferStarted = false;
                data = "";
            }

            if (!dataTransferStarted)
            {
                if (this->gprmcProtocolValidation.validateStartHeader(gpsData, startHeaderCount))
                {
                    startHeaderCount++;
                    if (startHeaderCount == string(CONFIG_GPS_START_HEADER).length())
                    {
                        dataTransferStarted = true;
                        data = CONFIG_GPS_START_HEADER;
                    }
                }
                else
                {
                    loggerWarn("IGps.getData", "Process warn", "data reset " + gpsData);

                    startHeaderCount = 0;
                    dataTransferStarted = false;
                    data = "";
                }
            }
            else
            {
                if (gpsData != CONFIG_PROTOCOL_LF && gpsData != CONFIG_PROTOCOL_CR)
                {
                    data += gpsData;
                }
            }
        }
    }

    return ErrorOrString(data);
}

ErrorOrString IGps::getData(int timeOut)
{
    loggerInfo("IGps.getData", "Process started");

    Timer timer;
    timer.setTimer(timeOut);

    ErrorOrString errorOrString;
    do
    {
        errorOrString = this->_getData(&timer);
        if (errorOrString.isError())
        {
            loggerError("IGps.getData", "Process error", errorOrString.getError().description);

            return errorOrString;
        }

    } while (!this->gprmcProtocolValidation.validate(errorOrString.getString()));

    loggerInfo("IGps.getData", "Process finished", errorOrString.getString());

    return errorOrString;
};

ErrorOrBool IGps::setup()
{
    gpsSerial.begin(CONFIG_GPS_SERIAL_BOUD_RATE);
    return ErrorOrBool(true);
    ErrorOrString errorOrString = this->getData(CONFIG_GPS_SETUP_TIMEOUT);
    if (errorOrString.isError())
    {
        return ErrorOrBool(errorOrString.getError());
    }

    return ErrorOrBool(true);
};
