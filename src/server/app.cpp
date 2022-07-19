
#include "utils/utils.h"
#include "server/app.h"

void App::start()
{
    loggerInfo("App.start", "Process started");
    this->SerialBT.begin(this->deviceName);
    loggerInfo("App.start", "Process finished", "Bluetooth now available");
};

int App::read()
{
    loggerInfo("App.read", "Process started");
    int serial = this->SerialBT.read();

    loggerInfo("App.read", "Process finished", serial != 0 ? "Serial: " + String(serial) : "");
    return serial;
};

String App::readString()
{
    loggerInfo("App.readString", "Process started");
    String serial = this->SerialBT.readString();

    loggerInfo("App.readString", "Process finished", serial != 0 ? "Serial: " + serial : "");
    return serial;
};

int App::avaliable()
{
    int avaliable = this->SerialBT.available();
    return avaliable;
};
