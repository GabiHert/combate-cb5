
#include "infra/implementation/lcd-implementation.h"
#include "utils/utils.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void Lcd::print(String message)
{
    loggerInfo("Lcd.display", "Process started", message);
    lcd.print(message);
    loggerInfo("Lcd.display", "Process finished");
};
void Lcd::setCursor(uint8_t column, uint8_t line)
{
    loggerInfo("Lcd.setCursor", "Process started");
    lcd.setCursor(column, line);
    loggerInfo("Lcd.setCursor", "Process finished");
};
void Lcd::setupDisplay()
{
    loggerInfo("Lcd.setupDisplay", "Process started");
    lcd.init();
    lcd.backlight();
    loggerInfo("Lcd.setupDisplay", "Process finished");
};

Lcd::Lcd(){};