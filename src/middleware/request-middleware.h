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
    ILcd *lcd;
    Cb *cb;
    Timer *timer;
    RequestController requestController;
    RequestValidationMiddleware requestValidationMiddleware;

public:
    RequestMiddleware(){};
    RequestMiddleware(Cb *cb, IGps *gps, ILcd *lcd, Timer *timer);
    ResponseModel execute(string request);
};

#endif // REQUEST_MIDDLEWARE