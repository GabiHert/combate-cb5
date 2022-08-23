
#include <Arduino.h>
#include "BluetoothSerial.h"

#include "config/config.h"
#include "utils/utils.h"

#include "server/app.h"

#include "domain/model/cb.h"

#include "middleware/request-middleware.h"
#include "controller/default-execution-gps-controller.h"
#include <iostream>
using namespace std;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

Cb cb("CB5 DEV");
App app(cb.id());
RequestMiddleware requestMiddleware(cb);
DefaultExecutionGpsController defaultExecutionGpsController;

void setup()
{
  Serial.begin(CONFIG().SERIAL_BOUD_RATE);

  loggerInfo("Setup", "Process started");

  app.start();
  cb.setup();

  cb.display.setCursor(0, 0);
  cb.display.print("Nome Bluetooth: ");
  cb.display.setCursor(0, 1);
  cb.display.print(cb.id());

  loggerInfo("Setup", "Process finished");
}

void loop()
{
  if (app.avaliable())
  {
    loggerInfo("main", "Process started", "Serial info. available");

    String request = app.readString();

    String response = requestMiddleware.execute(request);

    loggerInfo("main", "Process finished");

    app.write(response);
  }
  else
  {
    // defaultExecutionGpsController.execute(cb);
  }
}