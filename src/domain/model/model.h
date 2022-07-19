#include <Arduino.h>
#include "interfaces/interfaces.h"

class Cb
{
private:
    String id;
    byte location;

public:
    ILcd display;
    char alarmSiren;
    char poisonShots;
    char whellBoltsCounter;

    Cb(String id);
    ~Cb();

    String getId();
    boolean dose(int amount);
    byte getLocation();
};
