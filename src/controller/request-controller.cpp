#include "utils/utils.h"
#include "domain/dto/request-dto.h"
#include "config/config.h"
#include "exceptions/exceptions.h"
#include "domain/cb/cb.h"
#include "controller/request-controller.h"
#include "types/error-or-string.h"
#include <preferences.h>

RequestController::RequestController(Preferences *preferences, Cb *cb, IGps *gps, ILcd *lcd)
{
    this->cb = cb;

    this->lcd = lcd;

    this->renameUseCase = RenameUseCase(preferences, cb);

    this->doseUseCase = DoseUseCase(cb, this->lcd);

    this->getGpsLocationUseCase = GetGpsLocationUseCase(gps, cb, this->lcd);
};

RequestController::RequestController(){};

ErrorOrResponseDto RequestController::execute(RequestDto requestDto)
{

    loggerInfo("RequestController.execute", "Process started", "cbId: " + this->cb->getId());

    RequestModel requestModel(requestDto);
    this->cb->setRequestModel(requestModel);

    bool doseRequest = requestModel.getRequestType() == CONFIG_PROTOCOL_DOSE_REQUEST_TYPE;
    bool renameRequest = requestModel.getRequestType() == CONFIG_PROTOCOL_RENAME_REQUEST_TYPE;
    bool setupRequest = requestModel.getRequestType() == CONFIG_PROTOCOL_SETUP_REQUEST_TYPE;

    ErrorOrInt errorOrInt = this->cb->updateConnectedApplicators();
    if (errorOrInt.isError())
    {
        loggerError("DoseUseCase", "Process error", "could not update connected applicators");
        return ErrorOrResponseDto(EXCEPTIONS().NO_APPLICATORS_FOUND_ERROR);
    }

    if (doseRequest && requestModel.getDose() != CONFIG_PROTOCOL_DO_NOT_DOSE)
    {
        loggerInfo("RequestController.execute", "Dose request detected");
        ErrorOrBool errorOrBool = this->doseUseCase.execute(requestModel.getDose(), requestDto.getApplicators());
        if (errorOrBool.isError())
        {
            loggerError("requestController.execute", "Process error", "error: " + errorOrBool.getError().description);
            return ErrorOrResponseDto(errorOrBool.getError());
        }
    };

    if (renameRequest)
    {
        loggerInfo("RequestController.execute", "Rename request detected");
        ErrorOrBool errorOrBool = this->renameUseCase.execute(requestModel.getName());
        if (errorOrBool.isError())
        {
            loggerError("requestController.execute", "Process error", "error: " + errorOrBool.getError().description);
            return ErrorOrResponseDto(errorOrBool.getError());
        }
    }

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
