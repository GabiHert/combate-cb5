
#include "utils/utils.h"
#include "server/app.h"

App::App(String deviceName)
{
    this->deviceName = deviceName;
};

void App::start()
{
    loggerInfo("App.start", "Process started", "deviceName: " + deviceName);
    this->serialBT.begin(this->deviceName);
    loggerInfo("App.start", "Process finished", "Bluetooth now available");
};

int App::read()
{
    loggerInfo("App.read", "Process started");
    int serial = this->serialBT.read();

    loggerInfo("App.read", "Process finished", serial != 0 ? "Serial: " + String(serial) : "");
    return serial;
};

String App::readString()
{
    loggerInfo("App.readString", "Process started");
    String serial = this->serialBT.readString();

    loggerInfo("App.readString", "Process finished", serial != 0 ? "Serial: " + serial : "");
    return serial;
};

int App::avaliable()
{
    int avaliable = this->serialBT.available();
    return avaliable;
};

void App::write(String response)
{
    loggerInfo("App.start", "Process started");
    unsigned char responseLength = response.length();
    for (int i = 0; i <= responseLength; i++)
    {
        this->serialBT.write(response[i]);
    };

    loggerInfo("App.start", "Process finished", "Bluetooth now available");
};