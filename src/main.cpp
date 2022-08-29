
#include <Arduino.h>
#include "BluetoothSerial.h"

#include "config/config.h"
#include "utils/utils.h"

#include "infra/server/app.h"

#include "domain/cb/cb.h"
#include "middleware/request-middleware.h"
#include <iostream>
using namespace std;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

Cb cb("CB5 DEV");
App app(cb.getId());
RequestMiddleware requestMiddleware(cb);

void setup()
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
}

void loop()
{
  if (app.avaliable())
  {
    loggerInfo("main", "Process started", "Serial info. available");

    String request = app.readString();

    ResponseModel responseModel = requestMiddleware.execute(request);

    app.write(responseModel.toString());
    loggerInfo("main", "Process finished");
  }
}