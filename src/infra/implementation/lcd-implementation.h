
#include <Arduino.h>
#ifndef LCD_H
#define LCD_H

class Lcd
{
public:
    Lcd();
    void print(String message);
    void setCursor(uint8_t column, uint8_t line);
    void setupDisplay();
    void clearDisplay();
};
#endif // LCD_H