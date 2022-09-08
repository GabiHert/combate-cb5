
#include "useCase/get-gps-location-use-case.h"
#include "utils/utils.h"
#include "exceptions/error.h"

GetGpsLocationUseCase::GetGpsLocationUseCase(Cb *cb)
{
    this->cb = cb;
}
void GetGpsLocationUseCase::execute()
{
    try
    {
        loggerInfo("GetGpsUseCase.execute", "Process started");
        this->cb->gps.setLocation();
        loggerInfo("GetGpsUseCase.execute", "Process finished");
    }
    catch (Error err)
    {
        loggerError("getGpsLocationUseCase.execute", "Process error", "error: " + err.message());
        throw err;
    }
}
