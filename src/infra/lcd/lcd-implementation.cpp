#include "infra/lcd/lcd-interface.h"
#include "utils/utils.h"
#include "config/config.h"
#include <Arduino.h>
#include <string.h>
using namespace std;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void ILcd::print(string message, uint8_t column, uint8_t line)
{
    this->_shouldClear = true;
    setCursor(column, line);
    print(message);
    if (message.length() > 16 & !line)
        print(message.substr(16), 0, line + 1);
}
void ILcd::_print(string message, uint8_t column, uint8_t line)
{
    setCursor(column, line);
    print(message);
    if (message.length() > 16 & !line)
        print(message.substr(16), 0, line + 1);
}
void ILcd::printCentered(string message, uint8_t column, uint8_t line)
{
    print(centerString(message, CONFIG_lcd_COLUMNS_LENGTH), column, line);
}

void ILcd::printCentered(string message)
{
    print(centerString(message, CONFIG_lcd_COLUMNS_LENGTH));
}

void ILcd::print(string message)
{
    lcd.print(stdStringToArduinoString(message));
}

void ILcd::clear()
{
    this->_shouldClear = false;
    lcd.clear();
}

void ILcd::setCursor(uint8_t column, uint8_t line)
{
    lcd.setCursor(column, line);
}

ILcd::ILcd()
{
    lcd.init();
    lcd.backlight();
}

void ILcd::setGpsStatus(bool status)
{
    if (status)
    {
        _print("GPS", 0, 0);
    }
    else
    {
        _print("   ", 0, 0);
    }
};

void ILcd::setDoseStatus(unsigned char done, unsigned char target)
{
    _print(centerString(to_string(done) + "/" + to_string(target), 5), 11, 0);
};

void ILcd::setCBName(string name)
{
    _print(centerString(name, CONFIG_lcd_COLUMNS_LENGTH), 0, 1);
};

void ILcd::smartClear()
{
    if (this->_shouldClear)
        this->clear();
}

void ILcd::setVersion(string version)
{
    _print(centerString(version, 5), 5, 0);
}