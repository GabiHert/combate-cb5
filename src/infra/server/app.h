
#ifndef APP_H
#define APP_H
#include "BluetoothSerial.h"
#include <string>
using namespace std;

class App
{
private:
    string deviceName;
    BluetoothSerial serialBT;

public:
    App(string deviceName);
    void start();
    int read();
    void write(string response);
    string readstring();

    int avaliable();
};

#endif // APP_H