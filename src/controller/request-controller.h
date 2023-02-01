#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H
#include "domain/cb/cb.h"
#include <Arduino.h>
#include "useCase/turn-alarm-siren-on-use-case.h"
#include "useCase/dose-use-case.h"
#include "useCase/clear-wheel-bolts-counter-use-case.h"
#include "useCase/get-gps-location-use-case.h"
#include "domain/dto/response-dto.h"
#include "domain/dto/request-dto.h"
#include "types/error-or-response-dto.h"
#include "infra/gps/gps-interface.h"
class RequestController
{
private:
    Cb *cb;
    IDisplay *display;
    TurnAlarmSirenOnUseCase turnAlarmSirenOnUseCase;
    DoseUseCase doseUseCase;
    ClearWheelBoltsCounterUseCase clearWheelBoltsCounterUseCase;
    GetGpsLocationUseCase getGpsLocationUseCase;

public:
    RequestController(Cb *cb, IGps *gps, IDisplay *display);
    RequestController();

    ErrorOrResponseDto execute(RequestDto requestDto);
};
#endif // REQUEST_CONTROLLER_H