#include "utils/utils.h"
#include "domain/dto/request-dto.h"
#include "config/config.h"
#include "domain/cb/cb.h"
#include "controller/request-controller.h"
#include "useCase/clear-whell-bolts-counter-use-case.h"
#include "types/error-or-string.h"

RequestController::RequestController(Cb *cb, IGps *gps, IDisplay *display)
{
    this->cb = cb;

    this->display = display;

    loggerInfo("RequestController", "CONSTRUCTOR", "cbId: " + this->cb->getId());

    this->doseUseCase = DoseUseCase(cb, this->display);

    this->turnAlarmSirenOnUseCase = TurnAlarmSirenOnUseCase(cb);

    this->clearWhellBoltsCounterUseCase = ClearWhellBoltsCounterUseCase(cb);

    this->getGpsLocationUseCase = GetGpsLocationUseCase(gps, cb, this->display);
};

RequestController::RequestController(){};

ErrorOrResponseDto RequestController::execute(RequestDto requestDto)
{

    loggerInfo("RequestController.execute", "Process started", "cbId: " + this->cb->getId());

    RequestModel requestModel(requestDto);
    this->cb->setRequestModel(requestModel);

    bool turnAlarmSirenOnRequest = requestModel.getAlarmSiren() != CONFIG_PROTOCOL_ALARM_SIREN_OFF;
    bool doseRequest = requestModel.getDose() != CONFIG_PROTOCOL_DO_NOT_DOSE;
    bool clearWhellBoltsCounterRequest = requestModel.getWhellBoltsCounter() != CONFIG_PROTOCOL_DO_NOT_CLEAR_WHELL_BOLT_COUNTS;

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

    if (clearWhellBoltsCounterRequest)
    {
        loggerInfo("RequestController.execute", "Clear whell bolts counter request detected");
        ErrorOrBool errorOrBool = this->clearWhellBoltsCounterUseCase.execute();
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

    this->display->clear();
    this->display->print("PROCESSOS", 0, 0);
    this->display->print("FINALIZADOS", 0, 1);

    ResponseDto responseDto(*this->cb);
    loggerInfo("RequestController.execute", "Process finished", " gpsData: " + string(responseDto.getGpsData()));
    return ErrorOrResponseDto(responseDto);
};
