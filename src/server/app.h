#include "BluetoothSerial.h"

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
    String readString();

    int avaliable();
};