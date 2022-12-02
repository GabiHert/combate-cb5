
#include "utils/utils.h"
#include "infra/server/app.h"
#include "config/config.h"
#include <string.h>

App::App(Preferences *preferences)
{
    this->deviceName = arduinoStringToStdString(preferences->getString(CONFIG_PREFERENCES_DEVICE_NAME_KEY));
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

string App::readString()
{
    loggerInfo("App.readString", "Process started");
    string serial = arduinoStringToStdString(this->serialBT.readString());

    loggerInfo("App.readString", "Process finished", "serial: " + serial);
    return serial;
};

int App::available()
{
    int avaliable = this->serialBT.available();
    return avaliable;
};

void App::write(string response)
{
    loggerInfo("App.write", "Process started", response);
    if (response.length() > 0)
    {
        this->serialBT.print(response.c_str());
    }
    loggerInfo("App.write", "Process finished");
};

string App::getDeviceName() { return this->deviceName; }
void App::setDeviceName(string deviceName) { this->deviceName = deviceName; }