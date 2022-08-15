#ifndef REQUEST_MIDDLEWARE_H
#define REQUEST_MIDDLEWARE_H
#include "domain/model/cb.h"
#include "server/app.h"
#include "middleware/validation/request-validation-middleware.h"
#include "controller/request-controller.h"
#include <Arduino.h>

class RequestMiddleware
{
private:
    Cb cb;
    RequestController requestController;
    RequestValidationMiddleware requestValidationMiddleware;

public:
    RequestMiddleware(Cb cb);
    String execute(String request);
};

#endif // REQUEST_MIDDLEWARE