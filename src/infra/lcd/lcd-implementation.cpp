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
    loggerInfo("Lcd.print", "Process started", message);
    lcd.print(stdStringToArduinoString(message));
    loggerInfo("Lcd.print", "Process finished");
}

void ILcd::clear()
{
    this->_shouldClear = false;
    loggerInfo("Lcd.clear", "Process started");
    lcd.clear();
    loggerInfo("Lcd.clear", "Process finished");
}

void ILcd::setCursor(uint8_t column, uint8_t line)
{
    loggerInfo("Lcd.setCursor", "Process started");
    lcd.setCursor(column, line);
    loggerInfo("Lcd.setCursor", "Process finished");
}

ILcd::ILcd()
{
    loggerInfo("Lcd", "Constructor");
    lcd.init();
    lcd.backlight();
}

void ILcd::setGpsStatus(bool status)
{
    loggerInfo("Lcd.setGpsStatus", "Process started");
    if (status)
    {
        _print("GPS", 0, 0);
    }
    else
    {
        _print("   ", 0, 0);
    }
    loggerInfo("Lcd.setGpsStatus", "Process finished");
};

void ILcd::setDoseStatus(unsigned char done, unsigned char target)
{
    loggerInfo("Lcd.setDoseStatus", "Process started");
    _print(centerString(to_string(done) + "/" + to_string(target), 5), 11, 0);
    loggerInfo("Lcd.setDoseStatus", "Process finished");
};

void ILcd::setCBName(string name)
{
    loggerInfo("Lcd.setDoseStatus", "Process started");
    _print(centerString(name, CONFIG_lcd_COLUMNS_LENGTH), 0, 1);
    loggerInfo("Lcd.setDoseStatus", "Process finished");
};

void ILcd::smartClear()
{
    if (this->_shouldClear)
        this->clear();
}

void ILcd::setVersion(string version)
{
    loggerInfo("Lcd.setVersion", "Process started");
    _print(centerString(version, 5), 5, 0);
    loggerInfo("Lcd.setVersion", "Process finished");
}