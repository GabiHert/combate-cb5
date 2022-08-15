#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H
#include "domain/model/cb.h"
#include "server/app.h"
#include <Arduino.h>
#include "controller/builder/response-builder.h"

class RequestController
{
private:
    Cb cb;
    ResponseBuilder responseBuilder;

public:
    RequestController(Cb cb);
    RequestController();

    String execute(String request);
};
#endif // REQUEST_CONTROLLER_H