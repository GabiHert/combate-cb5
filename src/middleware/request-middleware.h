#ifndef REQUEST_MIDDLEWARE_H
#define REQUEST_MIDDLEWARE_H
#include "domain/cb/cb.h"
#include "middleware/validation/request-validation-middleware.h"
#include "controller/request-controller.h"
#include "domain/dto/response-dto.h"
#include <Arduino.h>
#include "domain/model/response-model.h"

class RequestMiddleware
{
private:
    Cb cb;
    RequestController requestController;
    RequestValidationMiddleware requestValidationMiddleware;

public:
    RequestMiddleware(Cb cb);
    ResponseModel execute(String request);
};

#endif // REQUEST_MIDDLEWARE