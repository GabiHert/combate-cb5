#include "utils/utils.h"
#include "domain/dto/request-dto.h"
#include "config/config.h"
#include "domain/cb/cb.h"
#include "controller/request-controller.h"
#include "useCase/clear-whell-bolts-counter-use-case.h"

RequestController::RequestController(Cb cb)
{
    this->cb = cb;

    this->doseUseCase = DoseUseCase(&cb);

    this->turnAlarmSirenOnUseCase = TurnAlarmSirenOnUseCase(&cb);

    this->clearWhellBoltsCounterUseCase = ClearWhellBoltsCounterUseCase(&cb);

    this->getGpsLocationUseCase = GetGpsLocationUseCase(&cb);
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

    this->getGpsLocationUseCase.execute();

    ResponseDto responseDto(this->cb);
    loggerInfo("RequestController.execute", "Process finished", " gpsData: " + String(responseDto.getGpsData()));
    return responseDto;
};
