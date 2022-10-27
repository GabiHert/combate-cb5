#include "utils/utils.h"
#include "useCase/turn-alarm-siren-on-use-case.h"
#

TurnAlarmSirenOnUseCase::TurnAlarmSirenOnUseCase(Cb *cb, IDisplay *display)
{
    this->cb = cb;
    this->display = display;
};

ErrorOrBool TurnAlarmSirenOnUseCase::execute()
{
    Timer timer;
    loggerInfo("TurnAlarmSirenOnUseCase", "Proces started");
    this->display->clear();
    this->display->print("ATIVANDO SIRENE.", 0, 0);
    timer.setTimer(1000);
    timer.wait();
    loggerInfo("TurnAlarmSirenOnUseCase", "Proces finished");
    return ErrorOrBool(true);
};