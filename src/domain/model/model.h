#include <Arduino.h>
#include "interfaces/interfaces.h"

class Cb
{
private:
    String id;

public:
    IDisplay display;
    IGps gps;
    char alarmSiren;
    char poisonShots;
    char whellBoltsCounter;

    Cb(String id);
    ~Cb();
    void setup();
    String getId();
    void dose(int amount);
};
