#include "utils/utils.h"
#include "domain/dto/request-dto.h"
#include "config/config.h"
#include "domain/cb/cb.h"
#include "controller/request-controller.h"
#include "types/error-or-string.h"

RequestController::RequestController(Cb *cb, IGps *gps, ILcd *lcd)
{
    this->cb = cb;

    this->lcd = lcd;

    loggerInfo("RequestController", "CONSTRUCTOR", "cbId: " + this->cb->getId());

    this->doseUseCase = DoseUseCase(cb, this->lcd);

    this->getGpsLocationUseCase = GetGpsLocationUseCase(gps, cb, this->lcd);
};

RequestController::RequestController(){};

ErrorOrResponseDto RequestController::execute(RequestDto requestDto)
{

    loggerInfo("RequestController.execute", "Process started", "cbId: " + this->cb->getId());

    RequestModel requestModel(requestDto);
    this->cb->setRequestModel(requestModel);

    bool doseRequest = requestModel.getDose() != CONFIG_PROTOCOL_DO_NOT_DOSE;

    if (doseRequest)
    {
        loggerInfo("RequestController.execute", "Dose request detected");
        ErrorOrBool errorOrBool = this->doseUseCase.execute(requestModel.getDose());
        if (errorOrBool.isError())
        {
            loggerError("requestController.execute", "Process error", "error: " + errorOrBool.getError().description);
            return ErrorOrResponseDto(errorOrBool.getError());
        }
    };

    ErrorOrString errorOrString = this->getGpsLocationUseCase.execute();

    if (errorOrString.isError())
    {
        loggerError("requestController.execute", "Process error", "error: " + errorOrString.getError().description);
        return ErrorOrResponseDto(errorOrString.getError());
    }

    this->cb->setLocation(errorOrString.getString());
    ResponseDto responseDto(*this->cb);
    loggerInfo("RequestController.execute", "Process finished", " gpsData: " + string(responseDto.getGpsData()));
    return ErrorOrResponseDto(responseDto);
};
