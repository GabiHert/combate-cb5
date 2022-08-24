#include "utils/utils.h"
#include "useCase/turn-alarm-siren-on-use-case.h"

TurnAlarmSirenOnUseCase::TurnAlarmSirenOnUseCase(Cb *cb)
{
    this->cb = cb;
};

void TurnAlarmSirenOnUseCase::execute()
{
    loggerInfo("TurnAlarmSirenOnUseCase", "Proces started");
    loggerInfo("TurnAlarmSirenOnUseCase", "Proces finished");
};