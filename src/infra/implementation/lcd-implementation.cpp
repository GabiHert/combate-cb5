#include "interfaces/lcd-interface.h"
#include "utils/utils.h"
#include <Arduino.h>
#include <string.h>
using namespace std;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void IDisplay::print(string message, uint8_t column, uint8_t line)
{
    setCursor(column, line);
    print(message);
}

void IDisplay::print(string message)
{
    loggerInfo("Lcd.print", "Process started", message);
    lcd.print(stdStringToArduinoString(message));
    loggerInfo("Lcd.print", "Process finished");
}

void IDisplay::clear()
{
    loggerInfo("Lcd.clear", "Process started");
    lcd.clear();
    loggerInfo("Lcd.clear", "Process finished");
}

void IDisplay::setCursor(uint8_t column, uint8_t line)
{
    loggerInfo("Lcd.setCursor", "Process started");
    lcd.setCursor(column, line);
    loggerInfo("Lcd.setCursor", "Process finished");
}

IDisplay::IDisplay()
{
    loggerInfo("Lcd", "Constructor");

    lcd.init();
    lcd.backlight();
}