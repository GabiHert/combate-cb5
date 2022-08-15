#include <Arduino.h>
#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H
#include "domain/model/cb.h"
#include "server/app.h"

class RequestController
{
private:
    Cb cb;

public:
    RequestController(Cb cb);
    RequestController();

    String execute(String request);
};
#endif // REQUEST_CONTROLLER_H