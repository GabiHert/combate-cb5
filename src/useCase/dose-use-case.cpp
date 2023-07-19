#include "utils/utils.h"
#include "exceptions/exceptions.h"
#include "useCase/dose-use-case.h"

DoseUseCase::DoseUseCase(Cb *cb, ILcd *lcd)
{
    this->lcd = lcd;
    this->cb = cb;
};

ErrorOrBool DoseUseCase::execute(char amount, vector<bool> applicators)
{

    for (int i = 0; i < applicators.size(); i++)
    {
        if (applicators.at(i) != this->cb->getConnectedApplicators().getBoolVector().at(i))
        {
            loggerError("DoseUseCase", "Process error", "applicator not found");
            return ErrorOrBool(EXCEPTIONS().NO_APPLICATORS_FOUND_ERROR);
        }
    }

    amount = asciiCharToNumber(amount);

    if (amount == 0)
        amount = 10;

    if (amount == -1)
    {
        loggerError("DoseUseCase", "Process error", "amount could not be parsed to number");
        return ErrorOrBool(EXCEPTIONS().PARSE_ERROR);
    }

    loggerInfo("DoseUseCase", "Process started", "amount: " + to_string(amount));

    ErrorOrBool errorOrBool = this->cb->dose(amount, applicators);
    if (errorOrBool.isError())
    {
        loggerError("doseUseCase.execute", "Process error", "error: " + errorOrBool.getError().description);
        return ErrorOrBool(errorOrBool.getError());
    }

    this->lcd->setDoseStatus(0, 0);

    loggerInfo("DoseUseCase", "Process finished");

    return ErrorOrBool(true);
};