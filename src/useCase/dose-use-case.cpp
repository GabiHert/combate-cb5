#include "utils/utils.h"
#include "useCase/dose-use-case.h"

DoseUseCase::DoseUseCase(Cb *cb)
{
    this->cb = cb;
};

ErrorOrBool DoseUseCase::execute(char amount)
{

    amount = asciiCharToNumber(amount);

    loggerInfo("DoseUseCase", "Process started", "amount: " + to_string((int)amount));

    ErrorOrBool errorOrBool = this->cb->dose(amount);
    if (errorOrBool.isError())
    {
        loggerError("doseUseCase.execute", "Process error", "error: " + errorOrBool.getError().description);
        return ErrorOrBool(errorOrBool.getError());
    }

    loggerInfo("DoseUseCase", "Process finished");
};