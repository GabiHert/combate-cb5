

#ifndef IDisplay_H
#define IDisplay_H
#include <Arduino.h>

class IDisplay
{
private:
public:
    IDisplay();
    void print(String message);
    void setupDisplay();
    void setCursor(uint8_t column, uint8_t line);
    void clearDisplay();
};
#endif // IDisplay_H