
#include "useCase/get-gps-location-use-case.h"
#include "utils/utils.h"

GetGpsLocationUseCase::GetGpsLocationUseCase(IGps *gps, Cb *cb, ILcd *lcd)
{
    this->lcd = lcd;
    this->cb = cb;
    this->gps = gps;
}
pair<string, ERROR_TYPE *> GetGpsLocationUseCase::execute()
{

    //loggerInfo("GetGpsUseCase.execute", "Process started");

    this->lcd->setGpsStatus(true);

    pair<string, ERROR_TYPE *> errorOrString = this->gps->getData();

    if (errorOrString.second != nullptr)
    {
        //loggerError("GetGpsUseCase.execute", "Process error", errorOrString.second->description);

        return errorOrString;
    }

    errorOrString.first = errorOrString.first.substr(7);
    this->lcd->setGpsStatus(false);

    return errorOrString;
}
