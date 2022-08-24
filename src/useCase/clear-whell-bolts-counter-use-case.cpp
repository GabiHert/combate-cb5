#include "useCase/clear-whell-bolts-counter-use-case.h"
#include "utils/utils.h"
ClearWhellBoltsCounterUseCase::ClearWhellBoltsCounterUseCase(Cb *cb)
{
    this->cb = cb;
}

void ClearWhellBoltsCounterUseCase::execute()
{
    loggerInfo("ClearWhellBoltsVounterUseCase.execute", "Process started");
    this->cb->clearWhellBoltsCount();
    loggerInfo("ClearWhellBoltsVounterUseCase.execute", "Process finished");
};