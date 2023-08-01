#include "utils/utils.h"
#include "domain/dto/request-dto.h"
#include "config/config.h"
#include "domain/cb/cb.h"
#include "controller/request-controller.h"

RequestController::RequestController(Cb *cb, IGps *gps, ILcd *lcd, Preferences *preferences)
{
    this->cb = cb;

    this->lcd = lcd;

    loggerInfo("RequestController", "CONSTRUCTOR", "cbId: " + this->cb->getId());

    this->doseUseCase = DoseUseCase(cb, this->lcd);

    this->getGpsLocationUseCase = GetGpsLocationUseCase(gps, cb, this->lcd);

    this->renameUseCase = RenameUseCase(lcd, cb, preferences);
};

RequestController::RequestController(){};

pair<ResponseDto, ERROR_TYPE *> RequestController::execute(RequestDto requestDto)
{

    loggerInfo("RequestController.execute", "Process started", "cbId: " + this->cb->getId());

    RequestModel requestModel(requestDto);
    this->cb->setRequestModel(requestModel);

    bool doseRequest = requestModel.getDose() != CONFIG_PROTOCOL_DO_NOT_DOSE;

    pair<string, ERROR_TYPE *> errorOrString = this->getGpsLocationUseCase.execute();
    if (errorOrString.second != nullptr)
    {
        loggerError("requestController.execute", "Process error", "error: " + errorOrString.second->description);
        return make_pair(ResponseDto(), errorOrString.second);
    }
    this->cb->setLocation(errorOrString.first);

    if (doseRequest)
    {
        loggerInfo("RequestController.execute", "Dose request detected");

        vector<bool> applicators = {requestModel.getLeftApplicator(), requestModel.getCenterApplicator(), requestModel.getLeftApplicator()};

        pair<bool, ERROR_TYPE *> errorOrBool = this->doseUseCase.execute(requestModel.getDose(), applicators);
        if (errorOrBool.second != nullptr)
        {
            loggerError("requestController.execute", "Process error", "error: " + errorOrBool.second->description);
            ResponseDto responseDto(*cb, errorOrBool.second->errorCode);
            return make_pair(responseDto, nullptr);
        }
    };

    ResponseDto responseDto(*this->cb);
    return make_pair(responseDto, nullptr);
};
