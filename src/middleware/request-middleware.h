#ifndef REQUEST_MIDDLEWARE_H
#define REQUEST_MIDDLEWARE_H
#include "domain/cb/cb.h"
#include "middleware/validation/request-validation-middleware.h"
#include "infra/lcd/lcd-interface.h"
#include "controller/request-controller.h"
#include "domain/dto/response-dto.h"
#include <Arduino.h>
#include "domain/model/response-model.h"
#include "infra/gps/gps-interface.h"

class RequestMiddleware
{
private:
    ILcd *_lcd;
    Cb *_cb;
    Timer *_timer;
    RequestController _requestController;
    RequestValidationMiddleware _requestValidationMiddleware;

public:
    RequestMiddleware(){};
    RequestMiddleware(Cb *cb, IGps *gps, ILcd *lcd, Timer *timer, Preferences *preferences);
    ResponseModel execute(string request);
    void systematic();
};

#endif // REQUEST_MIDDLEWARE