
#include "utils/utils.h"
#include "infra/server/app.h"
#include "config/config.h"
#include <string.h>

App::App(string deviceName)
{
    this->deviceName = deviceName;
};
App::App()
{
    this->deviceName = CONFIG().DEVICE_NAME;
}

void App::start()
{
    loggerInfo("App.start", "Process started", "deviceName: " + deviceName);
    this->serialBT.begin(stdStringToArduinoString(this->deviceName));
    loggerInfo("App.start", "Process finished", "Bluetooth now available");
};

int App::read()
{
    loggerInfo("App.read", "Process started");
    int serial = this->serialBT.read();

    loggerInfo("App.read", "Process finished", serial != 0 ? "Serial: " + to_string(serial) : "");
    return serial;
};

string App::readstring()
{
    loggerInfo("App.readstring", "Process started");
    string serial = arduinoStringToStdString(this->serialBT.readString());

    loggerInfo("App.readstring", "Process finished", "serial: " + serial);
    return serial;
};

int App::avaliable()
{
    int avaliable = this->serialBT.available();
    return avaliable;
};

void App::write(string response)
{
    loggerInfo("App.write", "Process started", response);
    unsigned char responseLength = response.length();
    for (int i = 0; i < responseLength; i++)
    {
        this->serialBT.write(response[i]);
    };

    loggerInfo("App.write", "Process finished", "Bluetooth now available");
};

string App::getDeviceName() { return this->deviceName; }