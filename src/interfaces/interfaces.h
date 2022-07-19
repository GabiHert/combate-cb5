#include <Arduino.h>

class ILcd
{
public:
    virtual void display(String message) = 0;
    virtual void setupDisplay() = 0;
    virtual void setCursor(unsigned char line, int column) = 0;
    virtual void clearDisplay(unsigned char line, int column) = 0;
};
