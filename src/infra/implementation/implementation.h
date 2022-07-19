#include <Arduino.h>

class Lcd
{
    Lcd();
    void print(String message);
    void setCursor(unsigned char line, int column);
    void setupDisplay();
};