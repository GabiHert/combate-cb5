
#ifndef APP_H
#define APP_H
#include "BluetoothSerial.h"
#include <string.h>
using namespace std;
class App
{
private:
    string deviceName;
    BluetoothSerial serialBT;

public:
    App();
    App(string deviceName);
    void start();
    int read();
    void write(string response);
    string readstring();
    string getDeviceName();

    int avaliable();
};

#endif // APP_H