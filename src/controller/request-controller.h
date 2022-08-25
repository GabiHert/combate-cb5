#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H
#include "domain/cb/cb.h"
#include "server/app.h"
#include <Arduino.h>
#include "useCase/turn-alarm-siren-on-use-case.h"
#include "useCase/dose-use-case.h"
#include "useCase/clear-whell-bolts-counter-use-case.h"
#include "useCase/get-gps-location-use-case.h"
#include "domain/dto/response-dto.h"
#include "domain/dto/request-dto.h"

class RequestController
{
private:
    Cb cb;
    TurnAlarmSirenOnUseCase turnAlarmSirenOnUseCase;
    DoseUseCase doseUseCase;
    ClearWhellBoltsCounterUseCase clearWhellBoltsCounterUseCase;
    GetGpsLocationUseCase getGpsLocationUseCase;

public:
    RequestController(Cb cb);
    RequestController();

    ResponseDto execute(RequestDto requestDto);
};
#endif // REQUEST_CONTROLLER_H