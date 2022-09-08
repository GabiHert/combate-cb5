
/*
#include "delivery/interfaces/cb5.h"
#include "domain/cb/cb.h"
#include "infra/server/app.h"
#include "middleware/request-middleware.h"
#include "utils/utils.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

Cb cb("CB5 DEV");
App app(cb.getId());
RequestMiddleware requestMiddleware(cb);
#include "BluetoothSerial.h"

void CB5::execute()
{
    if (app.avaliable())
    {
        loggerInfo("main", "Process started", "Serial info. available");

        string request = app.readstring();

        ResponseModel responseModel = requestMiddleware.execute(request);

        app.write(responseModel.tostring());
        loggerInfo("main", "Process finished");
    }
};
void CB5::setup()
{
    Serial.begin(CONFIG().SERIAL_BOUD_RATE);

    loggerInfo("Setup", "Process started");

    app.start();
    cb.setup();

    cb.display.setCursor(0, 0);
    cb.display.print("Nome Bluetooth: ");
    cb.display.setCursor(0, 1);
    cb.display.print(cb.getId());

    loggerInfo("Setup", "Process finished");
};
*/