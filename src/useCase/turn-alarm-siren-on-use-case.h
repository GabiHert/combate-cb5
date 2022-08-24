#ifndef TURN_ALARM_SIREN_ON_USE_CASE_H
#define TURN_ALARM_SIREN_ON_USE_CASE_H
#include "domain/cb/cb.h"

class TurnAlarmSirenOnUseCase
{
private:
    Cb *cb;

public:
    TurnAlarmSirenOnUseCase(Cb *cb);
    TurnAlarmSirenOnUseCase(){};
    void execute();
};

#endif