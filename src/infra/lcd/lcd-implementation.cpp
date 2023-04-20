#include "infra/lcd/lcd-interface.h"
#include "utils/utils.h"
#include "config/config.h"
#include <Arduino.h>
#include <string.h>
using namespace std;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void ILcd::print(string message, uint8_t column, uint8_t line)
{
    setCursor(column, line);
    print(message);
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