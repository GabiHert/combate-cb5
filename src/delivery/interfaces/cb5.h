
#ifndef CB5_H
#define CB5_H
#include "infra/server/app.h"

class CB5
{
private:
    App app;

public:
    CB5(){};
    void execute();
    void setup();
};

#endif