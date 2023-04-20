

#ifndef Ilcd_H
#define Ilcd_H
#include <LiquidCrystal_I2C.h>
#include <string>
using namespace std;
class ILcd
{
private:
public:
    ILcd();
    void print(string message);
    void print(string message, uint8_t column, uint8_t line);
    void printCentered(string message);
    void printCentered(string message, uint8_t column, uint8_t line);
    void setCursor(uint8_t column, uint8_t line);
    void clear();
};
#endif // Ilcd_H