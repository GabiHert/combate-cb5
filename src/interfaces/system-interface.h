#ifndef SYSTEM_INTERFACE_H
#define SYSTEM_INTERFACE_H
#include <string>
using namespace std;

class ISystem
{
private:
public:
    ISystem();
    void setupPort(unsigned char pin, unsigned char mode);
    void setPort(unsigned char pin, unsigned char state);
    int readDigitalPort(unsigned char pin);
    void serialPrintln(string message);
    void serialPrint(string message);
    string serialRead();
    int serialAvailable();
};

#endif