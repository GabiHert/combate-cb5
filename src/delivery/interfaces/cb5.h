
#ifndef CB5_H
#define CB5_H
#include "infra/server/app.h"
#include "infra/gps/gps-interface.h"
#include "domain/cb/cb.h"
#include "infra/lcd/lcd-interface.h"
#include "middleware/request-middleware.h"
#include "infra/lcd/lcd-interface.h"

class CB5
{
private:
    IDisplay *_display;
    App *_app;
    Cb *_cb;
    IGps _gps;
    RequestMiddleware _requestMiddleware;
    ISystem *_sys;
    Timer _timer;

    void _scanConnectedApplicators();
    void _initGps();

public:
    CB5(){};
    void execute();
    void setup(Preferences *preferences);
};

#endif