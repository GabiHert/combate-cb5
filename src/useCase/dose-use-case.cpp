#include "utils/utils.h"
#include "exceptions/error-type.h"
#include "useCase/dose-use-case.h"

DoseUseCase::DoseUseCase(Cb *cb, ILcd *lcd)
{
    this->lcd = lcd;
    this->cb = cb;
};

pair<bool, ERROR_TYPE *> DoseUseCase::execute(char amount)
{

    amount = asciiCharToNumber(amount);

    if (amount == 0)
        amount = 10;

    if (amount == -1)
    {
        loggerError("DoseUseCase", "Process error", "amount could not be parsed to number");
        return make_pair(false, ERROR_TYPES().PARSE_ERROR);
    }

    loggerInfo("DoseUseCase", "Process started", "amount: " + to_string(amount));

    pair<bool, ERROR_TYPE *> boolOrError = this->cb->dose(amount);
    if (boolOrError.second != nullptr)
    {
        loggerError("doseUseCase.execute", "Process error", "error: " + boolOrError.second->description);
        return make_pair(false, boolOrError.second);
    }

    this->lcd->setDoseStatus(0, 0);

    loggerInfo("DoseUseCase", "Process finished");

    return make_pair(true, nullptr);
};