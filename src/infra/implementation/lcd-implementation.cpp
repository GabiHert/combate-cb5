#include "interfaces/lcd-interface.h"
#include "utils/utils.h"
#include <Arduino.h>
#include <string.h>
using namespace std;

void IDisplay::print(string message, uint8_t column, uint8_t line)
{
    loggerInfo("Lcd.display", "Process started");
    this->setCursor(column, line);
    lcd.print(stdStringToArduinoString(message));
    loggerInfo("Lcd.dissplay", "Process finished");
}

void IDisplay::print(string message)
{
    loggerInfo("Lcd.display", "Process started", message);
    lcd.print(stdStringToArduinoString(message));
    loggerInfo("Lcd.dissplay", "Process finished");
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

    this->lcd.init();
    this->lcd.backlight();
}