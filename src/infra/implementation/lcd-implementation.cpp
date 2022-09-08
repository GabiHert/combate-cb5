#include "interfaces/lcd-interface.h"
#include "utils/utils.h"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <string.h>
using namespace std;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// TODO: se a mensagem ja estiver printada n printar novamente
//  guardar mensagem em atributo privado
void IDisplay::print(string message)
{
    loggerInfo("Lcd.display", "Process started");
    lcd.print(stdStringToArduinoString(message));
    loggerInfo("Lcd.dissplay", "Process finished");
}

void IDisplay::clearDisplay()
{
    loggerInfo("Lcd.clearDisplay", "Process started");
    lcd.clear();
    loggerInfo("Lcd.clearDisplay", "Process finished");
}

void IDisplay::setCursor(uint8_t column, uint8_t line)
{
    loggerInfo("Lcd.setCursor", "Process started");
    lcd.setCursor(column, line);
    loggerInfo("Lcd.setCursor", "Process finished");
}

void IDisplay::setupDisplay()
{
    loggerInfo("Lcd.setupDisplay", "Process started");
    lcd.init();
    lcd.backlight();
    loggerInfo("Lcd.setupDisplay", "Process finished");
}
IDisplay::IDisplay() {}