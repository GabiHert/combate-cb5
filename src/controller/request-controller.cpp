#include "utils/utils.h"
#include "domain/dto/request-dto.h"
#include "config/config.h"
#include "domain/cb/cb.h"
#include "controller/request-controller.h"
#include "useCase/clear-whell-bolts-counter-use-case.h"

RequestController::RequestController(Cb cb)
{
    this->cb = cb;

    DoseUseCase doseUseCase(&cb);
    this->doseUseCase = doseUseCase;

    TurnAlarmSirenOnUseCase turnAlarmSirenOnUseCase(&cb);
    this->turnAlarmSirenOnUseCase = turnAlarmSirenOnUseCase;

    ClearWhellBoltsCounterUseCase clearWhellBoltsCounterUseCase(&cb);
    this->clearWhellBoltsCounterUseCase = clearWhellBoltsCounterUseCase;
};

RequestController::RequestController(){};

ResponseDto RequestController::execute(RequestDto requestDto)
{
    loggerInfo("RequestController.execute", "Process started");

    RequestModel requestModel(requestDto);
    this->cb.setRequestModel(requestModel);

    bool turnAlarmSirenOnRequest = requestModel.getAlarmSiren() != CONFIG().ALARM_SIREN_OFF;
    bool doseRequest = requestModel.getDose() != CONFIG().PROTOCOL_DO_NOT_DOSE;
    bool clearWhellBoltsCounterRequest = requestModel.getWhellBoltsCounter() != CONFIG().PROTOCOL_DO_NOT_CLEAR_WHELL_BOLT_COUNTS;

    if (turnAlarmSirenOnRequest)
    {
        loggerInfo("RequestController.execute", "Turn alarm siren on Request detected");
        this->turnAlarmSirenOnUseCase.execute();
    };

    if (doseRequest)
    {
        loggerInfo("RequestController.execute", "Dose request detected");
        this->doseUseCase.execute(requestModel.getDose());
    };

    if (clearWhellBoltsCounterRequest)
    {
        loggerInfo("RequestController.execute", "Clear whell bolts counter request detected");
        this->clearWhellBoltsCounterUseCase.execute();
    };

    // TODO: getLocationUseCase.execute(&this.cb);

    ResponseDto responseDto(this->cb);
    loggerInfo("RequestController.execute", "Process finished");
    return responseDto;
};
