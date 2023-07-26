
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
    this->serialBT.begin(stdStringToArduinoString(this->deviceName));
};

int App::read()
{
    int serial = this->serialBT.read();
    return serial;
};

string App::readString()
{
    string serial = arduinoStringToStdString(this->serialBT.readString());
    return serial;
};

int App::available()
{
    int avaliable = this->serialBT.available();
    return avaliable;
};

void App::write(string response)
{
    if (response.length() > 0)
    {
        this->serialBT.print(response.c_str());
    }
};

string App::getDeviceName() { return this->deviceName; }
void App::setDeviceName(string deviceName) { this->deviceName = deviceName; }