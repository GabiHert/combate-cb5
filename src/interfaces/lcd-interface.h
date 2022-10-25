

#ifndef IDisplay_H
#define IDisplay_H
#include <LiquidCrystal_I2C.h>
#include <string>
using namespace std;
class IDisplay
{
private:
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

public:
    IDisplay();
    void print(string message);
    void print(string message, uint8_t column, uint8_t line);
    void setCursor(uint8_t column, uint8_t line);
    void clear();
};
#endif // IDisplay_H