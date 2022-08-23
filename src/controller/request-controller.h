#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H
#include "domain/cb/cb.h"
#include "server/app.h"
#include <Arduino.h>
#include "controller/builder/response-builder.h"
#include "useCase/turn-alarm-siren-on-use-case.h"
#include "useCase/dose-use-case.h"

#include "domain/dto/request-dto.h"

class RequestController
{
private:
    Cb cb;
    ResponseBuilder responseBuilder;
    TurnAlarmSirenOnUseCase turnAlarmSirenOnUseCase;
    DoseUseCase doseUseCase;

public:
    RequestController(Cb cb);
    RequestController();

    String execute(RequestDto requestDto);
};
#endif // REQUEST_CONTROLLER_H