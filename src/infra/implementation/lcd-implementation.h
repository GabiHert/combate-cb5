
#ifndef LCD_H
#define LCD_H
#include <Arduino.h>

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