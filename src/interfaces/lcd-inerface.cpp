#include "interfaces/interfaces.h"

void ILcd::print(String message)
{
    this->lcd.print(message);
}

void ILcd::clearDisplay()
{
    this->lcd.clearDisplay();
}

void ILcd::setCursor(unsigned char line, int column)
{
    this->lcd.setCursor(unsigned char line, int column);
}

void ILcd::setupDisplay()
{
    this->lcd.setupDisplay();
}