

#ifndef CB_H
#define CB_H

#include "interfaces/gps-interface.h"
#include "interfaces/lcd-interface.h"

class Cb
{
private:
    String _id;

public:
    IDisplay display;
    IGps gps;
    char alarmSiren;
    char poisonShots;
    char whellBoltsCounter[2];

    Cb(String id);
    Cb();
    void setup();
    String id();
    void dose(int amount);
};
#endif // CB_H