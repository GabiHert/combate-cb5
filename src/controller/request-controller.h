#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H
#include "domain/cb/cb.h"
#include <Arduino.h>
#include "useCase/dose-use-case.h"
#include "useCase/get-gps-location-use-case.h"
#include "useCase/rename-use-case.h"
#include "domain/dto/response-dto.h"
#include "domain/dto/request-dto.h"
#include "infra/gps/gps-interface.h"
#include <Preferences.h>
class RequestController
{
private:
    Cb *cb;
    ILcd *lcd;
    DoseUseCase _doseUseCase;
    GetGpsLocationUseCase _getGpsLocationUseCase;
    RenameUseCase _renameUseCase;
    char _systematicDosesApplied, _systematicMetersBetweenDose, _systematicMetersBetweenDoseParsed, _distanceRanMeters;
    ERROR_TYPE *_systematicError;
    unsigned long _lastDoseTimeMs, _lastCommunicationTimeMs;
    string _gpsData;

public:
    RequestController(Cb *cb, IGps *gps, ILcd *lcd, Preferences *preferences, Timer *timer);
    RequestController();

    pair<ResponseDto, ERROR_TYPE *> execute(RequestDto requestDto);
    ERROR_TYPE *systematic();
};

#endif // REQUEST_CONTROLLER_H