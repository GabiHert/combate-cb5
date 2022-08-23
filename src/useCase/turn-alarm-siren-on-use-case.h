#ifndef TURN_ALARM_SIREN_ON_USE_CASE_H
#define TURN_ALARM_SIREN_ON_USE_CASE_H
#include "domain/cb/cb.h"

class TurnAlarmSirenOnUseCase
{
public:
    TurnAlarmSirenOnUseCase();
    void execute(Cb *cb);
};

#endif