#include <Arduino.h>
#include "infra/implementation/implementation.h"
class IDisplay
{
private:
    Lcd display;

public:
    void print(String message);
    void setupDisplay();
    void setCursor(uint8_t column, uint8_t line);
    void clearDisplay();
};

class IGps
{
private:
    GpsNeo6M gps;

public:
    String getLocation();
    void setupGps();
};
