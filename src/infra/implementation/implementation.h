#include <Arduino.h>

class Lcd
{
public:
    Lcd();
    void print(String message);
    void setCursor(uint8_t column, uint8_t line);
    void setupDisplay();
    void clearDisplay();
};

class GpsNeo6M
{
public:
    GpsNeo6M();
    String getLocation();
    void setupGps();
};
