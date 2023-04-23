#ifndef TURN_ALARM_SIREN_ON_USE_CASE_H
#define TURN_ALARM_SIREN_ON_USE_CASE_H
#include "domain/cb/cb.h"
#include "types/error-or-boolean.h"
#include "infra/lcd/lcd-interface.h"

class TurnAlarmSirenOnUseCase
{
private:
    Cb *cb;
    ILcd *lcd;

public:
    TurnAlarmSirenOnUseCase(Cb *cb,ILcd *lcd);
    TurnAlarmSirenOnUseCase(){};
    ErrorOrBool execute();
};

#endif