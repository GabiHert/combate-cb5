
#ifndef APP_H
#define APP_H
#include "BluetoothSerial.h"

class App
{
private:
    String deviceName;
    BluetoothSerial serialBT;

public:
    App(String deviceName);
    void start();
    int read();
    void write(String response);
    String readString();

    int avaliable();
};

#endif // APP_H