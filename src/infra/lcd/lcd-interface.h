

#ifndef Ilcd_H
#define Ilcd_H
#include <LiquidCrystal_I2C.h>
#include "exceptions/error-type.h"
#include <string>
using namespace std;
class ILcd
{
private:
    bool _shouldClear;
    void _print(string message, uint8_t column, uint8_t line);
    char _systematicMetersBetweenDoseCache;

public:
    ILcd();
    void print(string message);
    void print(ERROR_TYPE *error);
    void print(string message, uint8_t column, uint8_t line);
    void printCentered(string message);
    void printCentered(string message, uint8_t column, uint8_t line);
    void setCursor(uint8_t column, uint8_t line);
    void clear();
    void setGpsStatus(bool active);
    void setDoseStatus(unsigned char done, unsigned char target);
    void setCBName(string name);
    void setVersion(string version);
    void setSystematicMetersBetweenDose(char systematicMetersBetweenDose);

    void smartClear();
};
#endif // Ilcd_H