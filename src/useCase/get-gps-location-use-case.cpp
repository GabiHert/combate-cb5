
#include "useCase/get-gps-location-use-case.h"
#include "utils/utils.h"

GetGpsLocationUseCase::GetGpsLocationUseCase(IGps *gps, Cb *cb, ILcd *lcd)
{
    this->lcd = lcd;
    this->cb = cb;
    this->gps = gps;
}
ErrorOrString GetGpsLocationUseCase::execute()
{

    loggerInfo("GetGpsUseCase.execute", "Process started");

    this->lcd->clear();
    this->lcd->print("CONSULTANDO LOC.", 0, 0);
    this->lcd->print("GPS. -> AGUARDE.", 0, 1);

    ErrorOrString errorOrString = this->gps->getData();

    if (errorOrString.isError())
    {
        loggerError("GetGpsUseCase.execute", "Process error", errorOrString.getError().description);

        return ErrorOrString(errorOrString.getError());
    }

    string result = errorOrString.getString();

    result = result.substr(7);
    result = result.replace(result.length() - 3, 1, "");

    loggerInfo("GetGpsUseCase.execute", "Process finished", result);

    return ErrorOrString(result);
}
