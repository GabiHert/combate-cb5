
#include "infra/implementation/implementation.h"
#include "utils/utils.h"

void Lcd::print(String message)
{
    loggerInfo("Lcd.display", "Process started", message);

    loggerInfo("Lcd.display", "Process finished");
};
void Lcd::setCursor(unsigned char line, int column)
{
    loggerInfo("Lcd.setCursor", "Process started");

    loggerInfo("Lcd.setCursor", "Process finished");
};
void Lcd::setupDisplay()
{
    loggerInfo("Lcd.setupDisplay", "Process started");

    loggerInfo("Lcd.setupDisplay", "Process finished");
};
