
#include "useCase/get-gps-location-use-case.h"
#include "utils/utils.h"

GetGpsLocationUseCase::GetGpsLocationUseCase(Cb *cb)
{
    this->cb = cb;
}
void GetGpsLocationUseCase::execute()
{
    loggerInfo("GetGpsUseCase.execute", "Process started");
    this->cb->gps.setLocation();
    loggerInfo("GetGpsUseCase.execute", "Process finished");
}
