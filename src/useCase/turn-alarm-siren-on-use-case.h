#ifndef TURN_ALARM_SIREN_ON_USE_CASE_H
#define TURN_ALARM_SIREN_ON_USE_CASE_H
#include "domain/cb/cb.h"
#include "types/error-or-boolean.h"
#include "interfaces/lcd-interface.h"

class TurnAlarmSirenOnUseCase
{
private:
    Cb *cb;
    IDisplay *display;

public:
    TurnAlarmSirenOnUseCase(Cb *cb,IDisplay *display);
    TurnAlarmSirenOnUseCase(){};
    ErrorOrBool execute();
};

#endif