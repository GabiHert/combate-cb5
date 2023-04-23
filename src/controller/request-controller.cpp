#include "utils/utils.h"
#include "domain/dto/request-dto.h"
#include "config/config.h"
#include "domain/cb/cb.h"
#include "controller/request-controller.h"
#include "useCase/clear-wheel-bolts-counter-use-case.h"
#include "types/error-or-string.h"

RequestController::RequestController(Cb *cb, IGps *gps, ILcd *lcd)
{
    this->cb = cb;

    this->lcd = lcd;

    loggerInfo("RequestController", "CONSTRUCTOR", "cbId: " + this->cb->getId());

    this->doseUseCase = DoseUseCase(cb, this->lcd);

    this->turnAlarmSirenOnUseCase = TurnAlarmSirenOnUseCase(cb, this->lcd);

    this->clearWheelBoltsCounterUseCase = ClearWheelBoltsCounterUseCase(cb);

    this->getGpsLocationUseCase = GetGpsLocationUseCase(gps, cb, this->lcd);
};

RequestController::RequestController(){};

ErrorOrResponseDto RequestController::execute(RequestDto requestDto)
{

    loggerInfo("RequestController.execute", "Process started", "cbId: " + this->cb->getId());

    RequestModel requestModel(requestDto);
    this->cb->setRequestModel(requestModel);

    bool turnAlarmSirenOnRequest = requestModel.getAlarmSiren() != CONFIG_PROTOCOL_ALARM_SIREN_OFF;
    bool doseRequest = requestModel.getDose() != CONFIG_PROTOCOL_DO_NOT_DOSE;
    bool clearWheelBoltsCounterRequest = requestModel.getWheelBoltsCounter() != CONFIG_PROTOCOL_DO_NOT_CLEAR_WHELL_BOLT_COUNTS;

    if (turnAlarmSirenOnRequest)
    {
        loggerInfo("RequestController.execute", "Turn alarm siren on Request detected");
        ErrorOrBool errorOrBool = this->turnAlarmSirenOnUseCase.execute();
        if (errorOrBool.isError())
        {
            loggerError("requestController.execute", "Process error", "error: " + errorOrBool.getError().description);
            return ErrorOrResponseDto(errorOrBool.getError());
        }
    };

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

    if (clearWheelBoltsCounterRequest)
    {
        loggerInfo("RequestController.execute", "Clear wheel bolts counter request detected");
        ErrorOrBool errorOrBool = this->clearWheelBoltsCounterUseCase.execute();
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
