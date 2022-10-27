

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

    if (app.avaliable())
    {
        loggerInfo("CB5.execute", "Process started", "Serial info. available");

        string request = app.readstring();

        ResponseModel responseModel = requestMiddleware.execute(request);

        string responseString = responseModel.toString();
        app.write(responseString);

        string separator;
        for (int i = 0; i < CONFIG_GPS_MESSAGE_LENGTH - (responseString.length() - 12); i++)
            separator += "-";

        app.write(separator);

        loggerInfo("CB5.execute", "Process finished");
    }
};

void CB5::setup()
{
    Serial.begin(CONFIG_SERIAL_BOUD_RATE); // TODO: usar classe System

    IDisplay display;
    Timer timer;

    display.clear();
    display.print("INICIALIZANDO CB", 0, 0);
    display.print("   AGUARDE...   ", 0, 1);

    loggerInfo("CB5.setup", "Process started");

    this->cb = Cb(&this->app);

    this->requestMiddleware = RequestMiddleware(&this->cb, &this->gps, &display);

    int retries = 0;
    for (retries; retries < CONFIG_GPS_MAX_SETUP_RETRIES; retries++)
    {
        display.clear();
        display.print(" INICIALIZANDO  ", 0, 0);
        display.print("GPS. -> AGUARDE.", 0, 1);

        ErrorOrBool errorOrBool = gps.setup();

        if (errorOrBool.isError())
        {
            display.clear();
            display.print(errorOrBool.getError().description, 0, 0);
            display.print(errorOrBool.getError().errorCode, 0, 1);

            timer.setTimer(1500);
            timer.wait();

            display.clear();
            display.print("RETENTANDO EM ", 0, 0);
            display.print(to_string(CONFIG_GPS_SETUP_RETRY_INTERVAL / 1000) + " SEGUNDOS", 0, 1);

            timer.setTimer(CONFIG_GPS_SETUP_RETRY_INTERVAL);
            timer.wait();
        }
        else
        {

            display.clear();
            display.print(" INICIALIZANDO  ", 0, 0);
            display.print("GPS. -> OK!", 0, 1);

            timer.setTimer(1500);
            timer.wait();
            break;
        }
    }

    retries = 0;
    for (retries; retries <= CONFIG_GPS_MAX_SETUP_RETRIES; retries++)
    {
        display.clear();
        display.print("VERIFICANDO DADOS", 0, 0);
        display.print("GPS.  AGUARDE...", 0, 1);

        ErrorOrString errorOrString = this->gps.getData();
        if (errorOrString.isError())
        {
            display.clear();
            display.print(errorOrString.getError().description, 0, 0);
            display.print(errorOrString.getError().errorCode, 0, 1);
        }
        else
        {
            if (gps.gprmcProtocolValidation.isDataReliable(errorOrString.getString()))
            {
                display.clear();
                display.print("VERIFICANDO DADOS", 0, 0);
                display.print("GPS. -> OK!", 0, 1);
                timer.setTimer(1000);
                timer.wait();

                break;
            }

            display.clear();
            display.print("VERIFICANDO DADOS", 0, 0);
            display.print("GPS. -> INCERTOS!", 0, 1);

            timer.setTimer(1500);
            timer.wait();

            display.clear();
            display.print("RETENTANDO EM ", 0, 0);
            display.print(to_string(CONFIG_GPS_SETUP_RETRY_INTERVAL / 1000) + " SEGUNDOS", 0, 1);

            timer.setTimer(CONFIG_GPS_SETUP_RETRY_INTERVAL);
            timer.wait();
        }
    }

    app.start();

    display.print("   BLUETOOTH:   ", 0, 0);
    display.print(cb.getId(), 0, 1);

    loggerInfo("CB5.setup", "Process finished");
};
