
#include <Arduino.h>
#include "BluetoothSerial.h"

#include "config/config.h"
#include "utils/utils.h"

#include "server/app.h"

#include "domain/model/cb.h"

#include "middleware/check-sum-validation-middleware.h"

#include "middleware/request-handler-middleware.h"

#include "controller/default-execution-gps-controller.h"
#include <iostream>
using namespace std;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

Cb cb("CB5 DEV");
App app(cb.getId());
CheckSumValidationMiddleware checkSumValidationMiddleware;
RequestHandlerMiddleware requestHandlerMiddleware;
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
  cb.display.print(cb.getId());

  loggerInfo("Setup", "Process finished");
}

void loop()
{
  if (app.avaliable())
  {
    loggerInfo("main", "Process started", "Serial info. available");
    String request = app.readString();

    // todo: should be         (request, cs     )
    bool isCsValid = checkSumValidationMiddleware.validate(request, request);

    if (isCsValid)
    {
      requestHandlerMiddleware.handle(request);
    }
    else
    {
      // todo:handle
    }
    loggerInfo("main", "Process finished");
  }
  else
  {
    defaultExecutionGpsController.execute(cb);
  }
}