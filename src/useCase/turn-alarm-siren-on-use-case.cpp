#include "utils/utils.h"
#include "useCase/turn-alarm-siren-on-use-case.h"

TurnAlarmSirenOnUseCase::TurnAlarmSirenOnUseCase(){};

void TurnAlarmSirenOnUseCase::execute(Cb *cb)
{
    loggerInfo("TurnAlarmSirenOnUseCase", "Proces started");
    loggerInfo("TurnAlarmSirenOnUseCase", "Proces finished");
};