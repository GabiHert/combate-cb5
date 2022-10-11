

#include "delivery/interfaces/cb5.h"
#include "domain/cb/cb.h"
#include "infra/server/app.h"
#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "BluetoothSerial.h"
#include "types/error-or-boolean.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

App app(CONFIG().DEVICE_NAME);
Cb cb(&app);
IGps gps;
RequestMiddleware requestMiddleware(cb, gps);

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
        for (int i = 0; i < CONFIG().GPS_MESSAGE_LENGTH - (responseString.length() - 12); i++)
        {
            separator += "-";
        }

        app.write(separator);

        loggerInfo("CB5.execute", "Process finished");
    }
};
void CB5::setup()
{
    Serial.begin(CONFIG().SERIAL_BOUD_RATE); // TODO: usar classe System
    loggerInfo("CB5.setup", "Process started");

    cb.setup();

    int retries = 0;
    for (retries; retries <= CONFIG().GPS_MAX_SETUP_RETRIES; retries++)
    {
        cb.display.clearDisplay();
        cb.display.print("TESTANDO GPS", 0, 0);
        cb.display.print("AGUARDE...", 0, 1);

        ErrorOrBool errorOrBool = gps.setup();
        if (errorOrBool.isError())
        {
            cb.display.clearDisplay();
            cb.display.print(errorOrBool.getError().description, 0, 0);
            cb.display.print(errorOrBool.getError().errorCode, 0, 1);
            Timer timer;
            timer.setTimer(3000);
            while (!timer.timedOut())
            {
            }
            cb.display.clearDisplay();
            cb.display.print("RETENTANDO EM ", 0, 0);
            cb.display.print(to_string(CONFIG().GPS_SETUP_RETRY_INTERVAL / 1000) + " SEGUNDOS", 0, 1);
            timer.setTimer(CONFIG().GPS_SETUP_RETRY_INTERVAL);
            while (!timer.timedOut())
            {
            }
            retries++;
        }
        else
        {

            cb.display.clearDisplay();
            cb.display.print("GPS TESTADO COM", 0, 0);
            cb.display.print("SUCESSO", 0, 1);
            break;
        }
    }

    app.start();

    cb.display.print("Nome Bluetooth: ", 0, 0);
    cb.display.print(cb.getId(), 0, 1);

    loggerInfo("CB5.setup", "Process finished");
};
