#include "utils/utils.h"
#include "useCase/dose-use-case.h"

DoseUseCase::DoseUseCase(Cb *cb)
{
    this->cb = cb;
};

void DoseUseCase::execute(char amount)
{
    amount = asciiCharToNumber(amount);

    loggerInfo("DoseUseCase", "Process started", "amount: " + String((int)amount));
    for (int dose = 0; dose < amount; dose++)
    {
        loggerInfo("DoseUseCase", "starting dose N: " + String(dose));

        this->cb->dose();
    }

    loggerInfo("DoseUseCase", "Process finished");
};