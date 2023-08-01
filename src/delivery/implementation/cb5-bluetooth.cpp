

#include "delivery/interfaces/cb5.h"
#include "domain/cb/cb.h"
#include "infra/server/app.h"
#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "BluetoothSerial.h"
#include <iostream>
#include "infra/validation/gprmc-protocol-validation.h"
#include <preferences.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void CB5::execute()
{

    if (this->_app->available())
    {
        this->_cb->clearStatus();
        loggerInfo("CB5.execute", "Process started", "Serial info. available");

        string request = this->_app->readString();

        ResponseModel responseModel = _requestMiddleware->execute(request);

        string responseString = responseModel.toString();
        this->_app->write(responseString);

        string separator;
        for (char i = 0; i < CONFIG_GPS_MESSAGE_LENGTH - (responseString.length() - 12); i++)
            separator += "-";

        this->_app->write(separator);

        loggerInfo("CB5.execute", "Process finished");
        this->_lcd->smartClear();
        this->_lcd->setGpsStatus(false);
        this->_lcd->setDoseStatus(0, 0);
        this->_lcd->setCBName(this->_cb->getId());
        this->_lcd->setVersion(CONFIG_CB5_SOFTWARE_VERSION);
    }
};

void CB5::_scanConnectedApplicators()
{
    loggerInfo("CB5._scanConnectedApplicators", "Process started");
    unsigned char connectedApplicators = 0;
    do
    {
        for (unsigned char i = 0; i < this->_cb->getPoisonApplicators().size(); i++)
        {
            if (this->_cb->getPoisonApplicators().at(i)->isConnected())
            {
                connectedApplicators++;
            }
        }

    } while (!connectedApplicators);

    this->_lcd->clear();
    this->_lcd->print("   DOSADORES    ", 0, 0);
    this->_lcd->print("CONECTADOS -> " + to_string(connectedApplicators), 0, 1);
    this->_timer->setTimer(2000)->wait();

    string applicator1Connected = this->_cb->getPoisonApplicators()[0]->isConnected() ? " 1 " : "";
    string applicator2Connected = this->_cb->getPoisonApplicators()[2]->isConnected() ? " 2 " : "";
    string applicator3Connected = this->_cb->getPoisonApplicators()[3]->isConnected() ? " 3 " : "";

    this->_lcd->clear();
    this->_lcd->printCentered("DOSADOR(ES)", 0, 0);
    this->_lcd->printCentered(applicator1Connected + applicator2Connected + applicator3Connected, 0, 1);
    this->_timer->setTimer(2000)->wait();
}

void CB5::_initGps()
{
    bool valid = false;

    do
    {
        this->_lcd->clear();
        this->_lcd->printCentered("SETUP", 0, 0);
        this->_lcd->print("GPS. -> AGUARDE.", 0, 1);

        pair<bool, ERROR_TYPE *> errorOrBool = _gps->setup();
        for (unsigned char retries = 0; retries <= CONFIG_GPS_MAX_SETUP_VALID_DATA_RETRIES; retries++)
        {

            pair<string, ERROR_TYPE *> errorOrString = this->_gps->getData();
            if (errorOrString.second != nullptr)
            {
                this->_lcd->clear();
                this->_lcd->print(errorOrString.second->description, 0, 0);
                this->_lcd->print(errorOrString.second->errorCode, 0, 1);
            }
            else
            {
                if (this->_gps->gprmcProtocolValidation.isDataReliable(errorOrString.first))
                {
                    this->_lcd->clear();
                    this->_lcd->printCentered("SINAL GPS", 0, 0);
                    this->_lcd->printCentered("OK", 0, 1);
                    this->_timer->setTimer(1000)->wait();
                    valid = true;
                    break;
                }

                this->_lcd->clear();
                this->_lcd->printCentered("SEM SINAL GPS", 0, 0);
                this->_lcd->printCentered("[" + to_string(retries) + "]", 0, 1);
                this->_timer->setTimer(CONFIG_GPS_SETUP_RETRY_INTERVAL)->wait();
            }
        }
    } while (!valid);
}

void CB5::setup(Preferences *preferences)
{
    this->_sys = new ISystem();
    loggerInfo("CB5.setup", "Process started");

    preferences->begin(CONFIG_PROJECT_NAME);
    preferences->putString("DEVICE_NAME", CONFIG_DEFAULT_DEVICE_NAME);

    this->_app = new App(preferences);
    this->_lcd = new ILcd();
    this->_timer = new Timer();
    this->_gps = new IGps(this->_lcd, this->_timer);
    this->_cb = new Cb(this->_app, this->_sys, this->_lcd);
    this->_requestMiddleware = new RequestMiddleware(this->_cb, this->_gps, this->_lcd, this->_timer);

    this->_initGps();
    this->_scanConnectedApplicators();

    this->_app->start();

    this->_lcd->clear();
    this->_lcd->printCentered("BLUETOOTH:", 0, 0);
    this->_lcd->printCentered(this->_cb->getId(), 0, 1);
    this->_timer->setTimer(1500)->wait();
    this->_lcd->clear();
    this->_lcd->setGpsStatus(false);
    this->_lcd->setDoseStatus(0, 0);
    this->_lcd->setCBName(this->_cb->getId());
    this->_lcd->setVersion(CONFIG_CB5_SOFTWARE_VERSION);
};
