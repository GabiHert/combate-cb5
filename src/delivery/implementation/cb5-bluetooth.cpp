

#include "delivery/interfaces/cb5.h"
#include "domain/cb/cb.h"
#include "infra/server/app.h"
#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "BluetoothSerial.h"
#include "types/error-or-boolean.h"
#include "infra/validation/gprmc-protocol-validation.h"
#include <preferences.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void CB5::execute()
{
    this->_display->print("AGUARDANDO IHM.", 0, 0);
    this->_display->printCentered(this->_cb->getId(), 0, 1);

    if (this->_app->available())
    {
        loggerInfo("CB5.execute", "Process started", "Serial info. available");

        string request = this->_app->readString();

        ResponseModel responseModel = _requestMiddleware.execute(request);

        string responseString = responseModel.toString();
        this->_app->write(responseString);

        string separator;
        for (int i = 0; i < CONFIG_GPS_MESSAGE_LENGTH - (responseString.length() - 12); i++)
            separator += "-";

        this->_app->write(separator);

        loggerInfo("CB5.execute", "Process finished");

        this->_display->clear();
    }
};

void CB5::_scanConnectedApplicators()
{
    loggerInfo("CB5._scanConnectedApplicators", "Process started");
    do
    {
        this->_cb->updateConnectedApplicators();
        if (this->_cb->getApplicators().isError())
        {
            this->_display->clear();
            this->_display->print(this->_cb->getApplicators().getError().description, 0, 0);
            this->_display->print(this->_cb->getApplicators().getError().errorCode, 0, 1);
            this->_timer.setTimer(1000);
            this->_timer.wait();
        }
    } while (this->_cb->getApplicators().isError());

    this->_display->clear();
    this->_display->print("   DOSADORES    ", 0, 0);
    this->_display->print("CONECTADOS -> " + to_string(this->_cb->getConnectedApplicators()), 0, 1);
    this->_timer.setTimer(1000);
    this->_timer.wait();

    string applicator1Connected = this->_cb->getApplicators().getBoolVector()[0] ? "S" : "N";
    string applicator2Connected = this->_cb->getApplicators().getBoolVector()[1] ? "S" : "N";
    string applicator3Connected = this->_cb->getApplicators().getBoolVector()[2] ? "S" : "N";

    this->_display->clear();
    this->_display->print("   DOSADORES    ", 0, 0);
    this->_display->printCentered("1:" + applicator1Connected + " 2:" + applicator2Connected + " 3:" + applicator3Connected, 0, 1);
    this->_timer.setTimer(1000);
    this->_timer.wait();

    loggerInfo("CB5._scanConnectedApplicators", "Process finished");
}

void CB5::_initGps()
{
    int retries = 0;
    for (retries; retries < CONFIG_GPS_MAX_SETUP_RETRIES; retries++)
    {
        this->_display->clear();
        this->_display->print(" INICIALIZANDO  ", 0, 0);
        this->_display->print("GPS. -> AGUARDE.", 0, 1);

        ErrorOrBool errorOrBool = _gps.setup();

        if (errorOrBool.isError())
        {
            this->_display->clear();
            this->_display->print(errorOrBool.getError().description, 0, 0);
            this->_display->print(errorOrBool.getError().errorCode, 0, 1);

            this->_timer.setTimer(1500);
            this->_timer.wait();

            this->_display->clear();
            this->_display->print("    AGUARDE     ", 0, 0);
            this->_display->print(to_string(CONFIG_GPS_SETUP_RETRY_INTERVAL / 1000) + " SEGUNDOS", 0, 1);

            this->_timer.setTimer(CONFIG_GPS_SETUP_RETRY_INTERVAL);
            this->_timer.wait();
        }
        else
        {

            this->_display->clear();
            this->_display->print(" INICIALIZANDO  ", 0, 0);
            this->_display->print("GPS. -> OK!", 0, 1);

            this->_timer.setTimer(1500);
            this->_timer.wait();
            break;
        }
    }

    retries = 0;
    for (retries; retries <= CONFIG_GPS_MAX_SETUP_VALID_DATA_RETRIES; retries++)
    {
        this->_display->clear();
        this->_display->print("VERIFICANDO DADOS", 0, 0);
        this->_display->print("GPS. -> AGUARDE. ", 0, 1);

        ErrorOrString errorOrString = this->_gps.getData();
        if (errorOrString.isError())
        {
            this->_display->clear();
            this->_display->print(errorOrString.getError().description, 0, 0);
            this->_display->print(errorOrString.getError().errorCode, 0, 1);
        }
        else
        {
            if (_gps.gprmcProtocolValidation.isDataReliable(errorOrString.getString()))
            {
                this->_display->clear();
                this->_display->print("VERIFICANDO DADOS", 0, 0);
                this->_display->print("GPS. -> OK!", 0, 1);
                this->_timer.setTimer(1000);
                this->_timer.wait();

                break;
            }

            this->_display->clear();
            this->_display->print("VERIFICANDO DADOS", 0, 0);
            this->_display->print("GPS. -> N OK!", 0, 1);

            this->_timer.setTimer(1500);
            this->_timer.wait();

            this->_display->clear();
            this->_display->print("[" + to_string(retries) + "] RETENTANDO", 0, 0);
            this->_display->print(to_string(CONFIG_GPS_SETUP_RETRY_INTERVAL / 1000) + " SEGUNDOS", 0, 1);

            this->_timer.setTimer(CONFIG_GPS_SETUP_RETRY_INTERVAL);
            this->_timer.wait();
        }
    }
}

void CB5::setup(Preferences *preferences)
{
    this->_sys = new ISystem();
    loggerInfo("CB5.setup", "Process started");

    preferences->begin(CONFIG_PROJECT_NAME);
    preferences->putString("DEVICE_NAME", CONFIG_DEFAULT_DEVICE_NAME);

    this->_app = new App(preferences);

    this->_display = new IDisplay();
    Timer timer;

    this->_display->clear();
    this->_display->print("INICIALIZANDO CB", 0, 0);
    this->_display->print("   AGUARDE...   ", 0, 1);
    this->_timer.setTimer(1000);
    this->_timer.wait();

    this->_cb = new Cb(this->_app, this->_sys, this->_display);

    this->_scanConnectedApplicators();

    this->_requestMiddleware = RequestMiddleware(this->_cb, &this->_gps, this->_display);

    this->_initGps();

    this->_app->start();

    this->_display->clear();
    this->_display->printCentered("BLUETOOTH:", 0, 0);
    this->_display->printCentered(this->_cb->getId(), 0, 1);
    this->_timer.setTimer(1500);
    this->_timer.wait();
    this->_display->clear();

    loggerInfo("CB5.setup", "Process finished");
};
