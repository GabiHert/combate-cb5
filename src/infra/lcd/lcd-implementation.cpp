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
        print("GPS", 0, 0);
    }
    else
    {
        print("   ", 0, 0);
    }
    loggerInfo("Lcd.setGpsStatus", "Process finished");
};

void ILcd::setDoseStatus(int done, int target)
{
    loggerInfo("Lcd.setDoseStatus", "Process started");
    print(centerString(to_string(done) + "/" + to_string(target), 12), 8, 0);
    loggerInfo("Lcd.setDoseStatus", "Process finished");
};