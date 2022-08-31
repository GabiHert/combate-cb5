#include "utils/utils.h"
#include "useCase/dose-use-case.h"

DoseUseCase::DoseUseCase(Cb *cb)
{
    this->cb = cb;
};

void DoseUseCase::execute(int amount)
{
    loggerInfo("DoseUseCase", "Process started", "amount: " + String(amount));
    loggerInfo("DoseUseCase", "amount: " + String(amount));

    for (int dose = 0; dose <= amount; dose++)
    {
        this->cb->dose();
    }
    loggerInfo("DoseUseCase", "Process finished");
};