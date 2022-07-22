#include "BluetoothSerial.h"

#ifndef APP_H
#define APP_H

class App
{
private:
    String deviceName;
    BluetoothSerial SerialBT;

public:
    App(String deviceName)
    {
        this->deviceName = deviceName;
    };
    void start();
    int read();
    void write(String response);
    String readString();

    int avaliable();
};

#endif // APP_H