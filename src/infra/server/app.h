
#ifndef APP_H
#define APP_H
#include "BluetoothSerial.h"
#include <string.h>
#include <Preferences.h>

using namespace std;
class App
{
private:
    string deviceName;
    BluetoothSerial serialBT;

public:
    App(Preferences *preferences);
    void start();
    int read();
    void write(string response);
    string readString();
    string getDeviceName();
    void setDeviceName(string deviceName);

    int available();
};

#endif // APP_H