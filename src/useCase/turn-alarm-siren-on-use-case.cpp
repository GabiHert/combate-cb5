#include "utils/utils.h"
#include "useCase/turn-alarm-siren-on-use-case.h"

TurnAlarmSirenOnUseCase::TurnAlarmSirenOnUseCase(Cb *cb, ILcd *lcd)
{
    this->cb = cb;
    this->lcd = lcd;
};

ErrorOrBool TurnAlarmSirenOnUseCase::execute()
{
    Timer timer;
    loggerInfo("TurnAlarmSirenOnUseCase", "Proces started");
    this->lcd->clear();
    this->lcd->print("ATIVANDO SIRENE.", 0, 0);
    timer.setTimer(1000);
    timer.wait();
    loggerInfo("TurnAlarmSirenOnUseCase", "Proces finished");
    return ErrorOrBool(true);
};