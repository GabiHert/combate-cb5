#include "utils/utils.h"
#include "useCase/dose-use-case.h"

DoseUseCase::DoseUseCase(Cb *cb, IDisplay *display)
{
    this->display = display;
    this->cb = cb;
};

ErrorOrBool DoseUseCase::execute(char amount)
{
    if (amount == 0)
        amount = 10;

    amount = asciiCharToNumber(amount);

    loggerInfo("DoseUseCase", "Process started", "amount: " + to_string(amount));

    this->display->clear();
    this->display->print("INICIO DOSAGEM", 0, 0);
    this->display->print(to_string(amount) + " DOSES", 0, 1);
    ErrorOrBool errorOrBool = this->cb->dose(amount);
    if (errorOrBool.isError())
    {
        loggerError("doseUseCase.execute", "Process error", "error: " + errorOrBool.getError().description);
        return ErrorOrBool(errorOrBool.getError());
    }

    this->display->clear();
    this->display->print("DOSAGEM FINALIZADA", 0, 0);

    loggerInfo("DoseUseCase", "Process finished");

    return ErrorOrBool(true);
};