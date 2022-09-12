#include "utils/utils.h"
#include "useCase/dose-use-case.h"
#include "exceptions/error.h"

DoseUseCase::DoseUseCase(Cb *cb)
{
    this->cb = cb;
};

void DoseUseCase::execute(char amount)
{
    try
    {
        amount = asciiCharToNumber(amount);

        loggerInfo("DoseUseCase", "Process started", "amount: " + to_string((int)amount));

        for (int dose = 0; dose < amount; dose++)
        {
            loggerInfo("DoseUseCase", "starting dose N: " + to_string(dose));

            this->cb->dose();
        }

        loggerInfo("DoseUseCase", "Process finished");
    }
    catch (Error err)
    {
        loggerError("doseUseCase.execute", "Process error", "error: " + err.message());
        throw err;
    }
};