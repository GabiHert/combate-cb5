#include "utils/utils.h"
#include "domain/dto/request-dto.h"
#include "config/config.h"
#include "domain/cb/cb.h"
#include "controller/request-controller.h"
#include "useCase/clear-whell-bolts-counter-use-case.h"
#include "exceptions/error.h"

RequestController::RequestController(Cb cb)
{
    this->cb = cb;
    loggerInfo("RequestController", "CONSTRUCTOR", "cbId: " + this->cb.getId());

    this->doseUseCase = DoseUseCase(&cb);

    this->turnAlarmSirenOnUseCase = TurnAlarmSirenOnUseCase(&cb);

    this->clearWhellBoltsCounterUseCase = ClearWhellBoltsCounterUseCase(&cb);

    this->getGpsLocationUseCase = GetGpsLocationUseCase(&cb);
};

RequestController::RequestController()
{
    loggerInfo("RequestController", "CONSTRUCTOR");
};

ResponseDto RequestController::execute(RequestDto requestDto)
{
    try
    {
        loggerInfo("RequestController.execute", "Process started", "cbId: " + this->cb.getId());

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
        loggerInfo("RequestController.execute", "Process finished", " gpsData: " + string(responseDto.getGpsData()));
        return responseDto;
    }
    catch (Error err)
    {
        loggerError("requestController.execute", "Process error", "error: " + err.message());
        throw err;
    }
};
