

#include "interfaces/gps-interface.h"
#include "interfaces/lcd-interface.h"

#ifndef CB_H
#define CB_H

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
    void setup();
    String getId();
    void dose(int amount);
};
#endif // CB_H