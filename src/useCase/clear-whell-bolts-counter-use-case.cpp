#include "useCase/clear-whell-bolts-counter-use-case.h"
#include "utils/utils.h"
ClearWhellBoltsCounterUseCase::ClearWhellBoltsCounterUseCase(Cb *cb)
{
    this->cb = cb;
}

ErrorOrBool ClearWhellBoltsCounterUseCase::execute()
{
    loggerInfo("ClearWhellBoltsVounterUseCase.execute", "Process started");
    this->cb->clearWhellBoltsCount();
    loggerInfo("ClearWhellBoltsVounterUseCase.execute", "Process finished");
    return ErrorOrBool(true);
};