#ifndef SYSTEM_INTERFACE_H
#define SYSTEM_INTERFACE_H

class ISystem
{
private:
public:
    ISystem(){};
    void setupPort(unsigned char pin, unsigned char mode);
    void setPort(unsigned char pin, unsigned char state);
    int readDigitalPort(unsigned char pin);
};

#endif