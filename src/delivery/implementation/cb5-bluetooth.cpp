

#include "delivery/interfaces/cb5.h"
#include "domain/cb/cb.h"
#include "infra/server/app.h"
#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "BluetoothSerial.h"

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

        app.write(responseModel.toString());
        loggerInfo("CB5.execute", "Process finished");
    }
};
void CB5::setup()
{
    gps.setup();
    cb.setup();
    Serial.begin(CONFIG().SERIAL_BOUD_RATE); // TODO: usar classe System

    app.start();
    loggerInfo("CB5.setup", "Process started");

    cb.display.setCursor(0, 0);
    cb.display.print("Nome Bluetooth: ");
    cb.display.setCursor(0, 1);
    cb.display.print(cb.getId());

    loggerInfo("CB5.setup", "Process finished");
};
