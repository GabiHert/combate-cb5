#include "interfaces/lcd-interface.h"

void IDisplay::print(String message)
{
    this->display.print(message);
}

void IDisplay::clearDisplay()
{
    this->display.clearDisplay();
}

void IDisplay::setCursor(uint8_t column, uint8_t line)
{
    this->display.setCursor(column, line);
}

void IDisplay::setupDisplay()
{
    this->display.setupDisplay();
}
IDisplay::IDisplay() {}