

#ifndef IDisplay_H
#define IDisplay_H
#include "infra/implementation/lcd-implementation.h"
#include <Arduino.h>

class IDisplay
{
private:
    Lcd display;

public:
    IDisplay();
    void print(String message);
    void setupDisplay();
    void setCursor(uint8_t column, uint8_t line);
    void clearDisplay();
};
#endif // IDisplay_H