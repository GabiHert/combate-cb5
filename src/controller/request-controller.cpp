#include "utils/utils.h"
#include "domain/dto/request-dto.h"
#include "config/config.h"
#include "domain/cb/cb.h"
#include "controller/request-controller.h"

RequestController::RequestController(Cb cb)
{
    this->cb = cb;
    DoseUseCase doseUseCase(&cb);
    this->doseUseCase = doseUseCase;
};
RequestController::RequestController(){};

String RequestController::execute(RequestDto requestDto)
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
        this->turnAlarmSirenOnUseCase.execute(&this->cb);
    };

    if (doseRequest)
    {
        loggerInfo("RequestController.execute", "Dose request detected");
        this->doseUseCase.execute(requestModel.getDose());
    };

    if (clearWhellBoltsCounterRequest)
    {
        loggerInfo("RequestController.execute", "Clear whell bolts counter request detected");
        // TODO: clearWhellBoltsCounterUseCase.execute(&this.cb);
    };

    // TODO: getLocationUseCase.execute(&this.cb);

    String response = responseBuilder.buildSuccess(cb);
    loggerInfo("RequestController.execute", "Process finished", "response: " + response);
    return response;
};
