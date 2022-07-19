#include <Arduino.h>
#include "infra/implementation/implementation.h"
class ILcd
{
private:
    Lcd lcd;

public:
    ILcd(){};
    void print(String message);
    void setupDisplay();
    void setCursor(unsigned char line, int column);
    void clearDisplay(unsigned char line, int column);
};
