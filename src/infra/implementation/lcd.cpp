
#include "interfaces/interfaces.h"
#include "utils/utils.h"

void ILcd::display(String message)
{
    loggerInfo("Lcd.display", "Process started", message);

    loggerInfo("Lcd.display", "Process finished");
};
void ILcd::setCursor(unsigned char line, int column)
{
    loggerInfo("Lcd.setCursor", "Process started");

    loggerInfo("Lcd.setCursor", "Process finished");
};
void ILcd::setupDisplay()
{
    loggerInfo("Lcd.setupDisplay", "Process started");

    loggerInfo("Lcd.setupDisplay", "Process finished");
};
