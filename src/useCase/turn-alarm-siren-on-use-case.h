#ifndef TURN_ALARM_SIREN_ON_USE_CASE_H
#define TURN_ALARM_SIREN_ON_USE_CASE_H
#include "domain/cb/cb.h"
#include "types/error-or-boolean.h"

class TurnAlarmSirenOnUseCase
{
private:
    Cb *cb;

public:
    TurnAlarmSirenOnUseCase(Cb *cb);
    TurnAlarmSirenOnUseCase(){};
    ErrorOrBool execute();
};

#endif