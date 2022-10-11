

#ifndef IDisplay_H
#define IDisplay_H
#include <string>
using namespace std;
class IDisplay
{
private:
public:
    IDisplay();
    void print(string message);
    void print(string message, uint8_t column, uint8_t line);
    void setupDisplay();
    void setCursor(uint8_t column, uint8_t line);
    void clearDisplay();
};
#endif // IDisplay_H