#include "infra/gps/gps-interface.h"
#include <HardwareSerial.h>
#include "utils/utils.h"
#include "config/config.h"
#include <Arduino.h>
#include <string.h>
#include "exceptions/error-type.h"
using namespace std;

HardwareSerial gpsSerial(2);

IGps::IGps(ILcd *lcd, Timer *timer)
{
    this->_lcd = lcd;
    this->timer = timer;
}

ErrorOrString IGps::_getData(Timer *timer)
{
    // ErrorOrString errorOrString = ErrorOrString("$GPRMC,001220.00,A,3001.89425,S,05109.81024,W,0.374,,240719,,,N*75");
    // return errorOrString;
    string data = "";
    char startHeaderCount = 0;
    int gpsData;
    bool dataTransferStarted = false;
    while (gpsSerial.available())
    {
        gpsSerial.read();
    }

    while (gpsData != CONFIG_PROTOCOL_LF || !dataTransferStarted)
    {

        if (timer->timedOut())
        {
            loggerError("IGps.getData", "Process error", "Gps timed out");
            return ErrorOrString(ERROR_TYPES().GPS_TIME_OUT);
        }

        if (gpsSerial.available() > 0)
        {
            gpsData = gpsSerial.read();

            if (gpsData == '$' && dataTransferStarted)
            {
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
    loggerInfo("IGps._getData", "Process finished", data);

    return ErrorOrString(data);
}

ErrorOrString IGps::getData(int timeOut)
{
    loggerInfo("IGps.getData", "Process started");

    this->timer->setTimer(timeOut);

    ErrorOrString errorOrString;
    do
    {
        errorOrString = this->_getData(timer);
        if (errorOrString.isError())
        {
            loggerError("IGps.getData", "Process error", errorOrString.getError()->description);

            return errorOrString;
        }

    } while (!this->gprmcProtocolValidation.validate(errorOrString.getString()));

    loggerInfo("IGps.getData", "Process finished", errorOrString.getString());

    return errorOrString;
};

pair<bool, ERROR_TYPE *> IGps::setup()
{
    loggerInfo("IGps.setup", "Process started");

    unsigned char i = 0;

    loggerInfo("IGps.setup", "set baud 19200");
    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("BAUD 19200 I", 0, 1);
    gpsSerial.begin(CONFIG_GPS_SERIAL_BAUD_RATE, SERIAL_8N2, CONFIG_PORT_GPIO_GPS_RX, CONFIG_PORT_GPIO_GPS_TX);
    this->timer->setTimer(1000)->wait();

    loggerInfo("IGps.setup", "set 10hz");
    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("10Hz [1]", 0, 1);

    for (i = 0; i < 14; i++)
        gpsSerial.write(CONFIG().UBLOX_SETUP_SET_10HZ_1[i]);

    loggerInfo("IGps.setup", "set baud 9600");
    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("BAUD 9600 I", 0, 1);

    gpsSerial.begin(9600, SERIAL_8N2, CONFIG_PORT_GPIO_GPS_RX, CONFIG_PORT_GPIO_GPS_TX);
    this->timer->setTimer(3000)->wait();

    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("10Hz [2]", 0, 1);
    loggerInfo("IGps.setup", "set 10hz");
    for (i = 0; i < 14; i++)
        gpsSerial.write(CONFIG().UBLOX_SETUP_SET_10HZ_1[i]);
    this->timer->setTimer(3000)->wait();

    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("GLL OFF", 0, 1);
    loggerInfo("IGps.setup", "disable GLL");
    for (i = 0; i < CONFIG().UBLOX_SETUP_DISABLE_GLL.size(); i++)
        gpsSerial.write(CONFIG().UBLOX_SETUP_DISABLE_GLL.at(i));
    this->timer->setTimer(1000)->wait();

    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("GSV OFF", 0, 1);
    loggerInfo("IGps.setup", "disable GSV");
    for (i = 0; i < CONFIG().UBLOX_SETUP_DISABLE_GSV.size(); i++)
        gpsSerial.write(CONFIG().UBLOX_SETUP_DISABLE_GSV.at(i));
    this->timer->setTimer(1000)->wait();

    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("GSA OFF", 0, 1);
    loggerInfo("IGps.setup", "disable GSA");
    for (i = 0; i < CONFIG().UBLOX_SETUP_DISABLE_GSA.size(); i++)
        gpsSerial.write(CONFIG().UBLOX_SETUP_DISABLE_GSA.at(i));
    this->timer->setTimer(1000)->wait();

    loggerInfo("IGps.setup", "disable GGA");
    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("GGA OFF", 0, 1);
    for (i = 0; i < CONFIG().UBLOX_SETUP_DISABLE_GGA.size(); i++)
        gpsSerial.write(CONFIG().UBLOX_SETUP_DISABLE_GGA.at(i));
    this->timer->setTimer(1000)->wait();

    loggerInfo("IGps.setup", "disable VTG");
    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("VGT OFF", 0, 1);
    for (i = 0; i < CONFIG().UBLOX_SETUP_DISABLE_VTG.size(); i++)
        gpsSerial.write(CONFIG().UBLOX_SETUP_DISABLE_VTG.at(i));
    this->timer->setTimer(1000)->wait();

    loggerInfo("IGps.setup", "disable ZDA");
    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("ZDA OFF", 0, 1);
    for (i = 0; i < CONFIG().UBLOX_SETUP_DISABLE_ZDA.size(); i++)
        gpsSerial.write(CONFIG().UBLOX_SETUP_DISABLE_ZDA.at(i));
    this->timer->setTimer(1000)->wait();

    loggerInfo("IGps.setup", "set baud 19200");
    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("BAUD 19200 E", 0, 1);

    for (i = 0; i < CONFIG().UBLOX_SETUP_SET_SERIAL_BAUD_19200.size(); i++)
        gpsSerial.write(CONFIG().UBLOX_SETUP_SET_SERIAL_BAUD_19200.at(i));
    this->timer->setTimer(4000)->wait();

    loggerInfo("IGps.setup", "begin baud 19200");
    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("BAUD 19200 I", 0, 1);
    gpsSerial.begin(CONFIG_GPS_SERIAL_BAUD_RATE, SERIAL_8N2, CONFIG_PORT_GPIO_GPS_RX, CONFIG_PORT_GPIO_GPS_TX);
    this->timer->setTimer(1000)->wait();

    loggerInfo("IGps.setup", "set 10hz");
    this->_lcd->clear();
    this->_lcd->printCentered("SET GPS", 0, 0);
    this->_lcd->printCentered("10Hz [3]", 0, 1);
    for (i = 0; i < 16; i++)
        gpsSerial.write(CONFIG().UBLOX_SETUP_SET_10HZ[i]);
    this->timer->setTimer(3000)->wait();

    loggerInfo("IGps.setup", "Process finished");

    return make_pair(true, nullptr);
};
