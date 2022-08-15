#include "controller/request-controller.h"
#include "utils/utils.h"
#include "domain/dto/request-dto.h"
#include "config/config.h"
#include "domain/model/cb.h"

RequestController::RequestController(Cb cb)
{
    this->cb = cb;
}
RequestController::RequestController()
{
}

String RequestController::execute(String request)
{
    loggerInfo("RequestController.execute", "Process started");

    RequestDto requestDto(request);

    bool turnAlarmSirenOnRequest = requestDto.alarmSiren() != CONFIG().ALARM_SIREN_OFF;
    bool doseRequest = requestDto.dose() != CONFIG().PROTOCOL_DO_NOT_DOSE;
    bool clearWhellBoltsCounterRequest = requestDto.whellBoltsCounter() != CONFIG().PROTOCOL_DO_NOT_CLEAR_WHELL_BOLT_COUNTS;

    if (turnAlarmSirenOnRequest)
    {
        loggerInfo("RequestController.execute", "Turn alarm siren on Request detected");
        // TODO: turnAlarmSirenOnUseCase.execute(&this.cb);
    };

    if (doseRequest)
    {
        loggerInfo("RequestController.execute", "Dose request detected");
        // TODO: doseUseCase.execute(&this.cb);
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
