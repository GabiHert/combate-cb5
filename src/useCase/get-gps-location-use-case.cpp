
#include "useCase/get-gps-location-use-case.h"
#include "utils/utils.h"

GetGpsLocationUseCase::GetGpsLocationUseCase(IGps *gps, Cb *cb)
{
    this->cb = cb;
    this->gps = gps;
}
ErrorOrString GetGpsLocationUseCase::execute()
{

    loggerInfo("GetGpsUseCase.execute", "Process started");

    this->cb->display.clearDisplay();
    this->cb->display.print("INICIO CONSULTA", 0, 0);
    this->cb->display.print("GPS", 0, 1);

    ErrorOrString errorOrString = ErrorOrString("$GPRMC,001220.00,A,3001.89425,S,05109.81024,W,0.374,,240719,,,A75"); // this->gps->getData(); 

    if (errorOrString.isError())
    {
        loggerError("GetGpsUseCase.execute", "Process error", errorOrString.getError().description);

        return ErrorOrString(errorOrString.getError());
    }
    string result = errorOrString.getString();

    result = result.substr(7);

    loggerInfo("GetGpsUseCase.execute", "Process finished", result);

    return ErrorOrString(result);
}
