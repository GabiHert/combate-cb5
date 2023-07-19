#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H
#include "domain/cb/cb.h"
#include <Arduino.h>
#include "useCase/dose-use-case.h"
#include "useCase/rename-use-case.h"
#include "useCase/get-gps-location-use-case.h"
#include "domain/dto/response-dto.h"
#include "domain/dto/request-dto.h"
#include "types/error-or-response-dto.h"
#include "infra/gps/gps-interface.h"
class RequestController
{
private:
    Cb *cb;
    ILcd *lcd;
    DoseUseCase doseUseCase;
    GetGpsLocationUseCase getGpsLocationUseCase;
    RenameUseCase renameUseCase;

public:
    RequestController(Preferences *preferences, Cb *cb, IGps *gps, ILcd *lcd);
    RequestController();

    ErrorOrResponseDto execute(RequestDto requestDto);
};
#endif // REQUEST_CONTROLLER_H