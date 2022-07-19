#include <Arduino.h>
#include "config/config.h"
#include "BluetoothSerial.h"
#include "domain/model/model.h"
#include "server/app.h"
#include "utils/utils.h"
#include "middleware/middleware.h"
#include <iostream>

using namespace std;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

Cb cb("CB5 DEV");
App app(cb.getId());
CheckSumValidation checkSumValidation;
RequestHandler requestHandler;

void setup()
{
  loggerInfo("Setup", "Process started");
  Serial.begin(CONFIG().SERIAL_BOUD_RATE);
  app.start();
  cb.setupDisplay();
  cb.display("")
  loggerInfo("Setup", "Process finished");
}

void loop()
{
  if (app.avaliable())
  {
    loggerInfo("main", "Process started", "Serial info. available");
    String request = app.readString();
    // todo: should be         (request, cs     )
    bool isCsValid = checkSumValidation.validate(request, request);

    if (isCsValid)
    {
      requestHandler.handle(request);
    }
    else
    {
      // todo:handle
    }
    loggerInfo("main", "Process finished");
  }
  else
  {
    // todo: call controller to def routine
  }
}