
#include "useCase/get-gps-location-use-case.h"
#include "utils/utils.h"

GetGpsLocationUseCase::GetGpsLocationUseCase(IGps *gps)
{
    this->gps = gps;
}
ErrorOrString GetGpsLocationUseCase::execute()
{

    loggerInfo("GetGpsUseCase.execute", "Process started");
    ErrorOrString errorOrString = this->gps->getData();

    if (errorOrString.isError())
    {
        loggerError("GetGpsUseCase.execute", "Process error", errorOrString.getError().description);

        return ErrorOrString(errorOrString.getError());
    }
    string result = errorOrString.getString();

    int i;
    for (i = 0; i < result.length(); i++)
    {
        if (result[i] == ',')
        {
            break;
        }
    }

    result = result.substr(i - 1);
    loggerInfo("GetGpsUseCase.execute", "Process finished", result);

    return ErrorOrString(result);
}
