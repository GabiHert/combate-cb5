

#include "delivery/interfaces/cb5.h"
#include "domain/cb/cb.h"
#include "infra/server/app.h"
#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "BluetoothSerial.h"
#include "types/error-or-boolean.h"
#include "infra/validation/gprmc-protocol-validation.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void CB5::execute()
{
    this->_display->print("AGUARDANDO IHM.", 0, 0);
    this->_display->print(this->_cb.getId(), 0, 1);

    if (_app.avaliable())
    {
        loggerInfo("CB5.execute", "Process started", "Serial info. available");

        string request = _app.readstring();

        ResponseModel responseModel = _requestMiddleware.execute(request);

        string responseString = responseModel.toString();
        _app.write(responseString);

        string separator;
        for (int i = 0; i < CONFIG_GPS_MESSAGE_LENGTH - (responseString.length() - 12); i++)
            separator += "-";

        _app.write(separator);

        loggerInfo("CB5.execute", "Process finished");

        this->_display->clear();
    }
};

void CB5::_scanConnectedApplicators()
{
    this->_cb = Cb(&this->_app, this->_sys);

    do
    {
        _cb.updateConnectedApplicators();
        if (_cb.getConnectedApplicators().isError())
        {
            this->_display->clear();
            this->_display->print(_cb.getConnectedApplicators().getError().description, 0, 0);
            this->_display->print(_cb.getConnectedApplicators().getError().errorCode, 0, 1);
            this->_timer.setTimer(1000);
            this->_timer.wait();
        }
    } while (_cb.getConnectedApplicators().isError());

    this->_display->clear();
    this->_display->print("   DOSADORES    ", 0, 0);
    this->_display->print("CONECTADOS -> " + to_string(int(_cb.getConnectedApplicators().getBoolVector().size())), 0, 1);
    this->_timer.setTimer(1000);
    this->_timer.wait();
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

void CB5::setup()
{
    this->_sys = new ISystem();
    this->_display = new IDisplay();
    Timer timer;

    this->_display->clear();
    this->_display->print("INICIALIZANDO CB", 0, 0);
    this->_display->print("   AGUARDE...   ", 0, 1);
    this->_timer.setTimer(1000);
    this->_timer.wait();

    loggerInfo("CB5.setup", "Process started");

    this->_scanConnectedApplicators();

    this->_requestMiddleware = RequestMiddleware(&this->_cb, &this->_gps, this->_display);

    this->_initGps();

    _app.start();

    this->_display->clear();
    this->_display->print("   BLUETOOTH:   ", 0, 0);
    this->_display->print(_cb.getId(), 0, 1);
    this->_timer.setTimer(1500);
    this->_timer.wait();
    loggerInfo("CB5.setup", "Process finished");
};
