
#ifndef CB5_H
#define CB5_H
#include "infra/server/app.h"
#include "interfaces/gps-interface.h"
#include "domain/cb/cb.h"
#include "interfaces/lcd-interface.h"
#include "middleware/request-middleware.h"
#include "interfaces/lcd-interface.h"

class CB5
{
private:
    IDisplay *display;
    App app;
    Cb cb;
    IGps gps;
    RequestMiddleware requestMiddleware;

public:
    CB5(){};
    void execute();
    void setup();
};

#endif