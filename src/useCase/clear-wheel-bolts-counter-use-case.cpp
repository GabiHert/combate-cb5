#include "useCase/clear-wheel-bolts-counter-use-case.h"
#include "utils/utils.h"
ClearWheelBoltsCounterUseCase::ClearWheelBoltsCounterUseCase(Cb *cb)
{
    this->cb = cb;
}

ErrorOrBool ClearWheelBoltsCounterUseCase::execute()
{
    loggerInfo("ClearWheelBoltsVounterUseCase.execute", "Process started");
    this->cb->clearWheelBoltsCount();
    loggerInfo("ClearWheelBoltsVounterUseCase.execute", "Process finished");
    return ErrorOrBool(true);
};