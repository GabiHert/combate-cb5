#include <Arduino.h>
#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H
#include "domain/model/cb.h"
#include "server/app.h"

class RequestController
{
private:
    Cb *cb;
    App *app;

public:
    RequestController(Cb *cb, App *app);
    void execute(String request);
};
#endif // REQUEST_CONTROLLER_H