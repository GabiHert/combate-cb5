#include "utils/utils.h"
#include "domain/dto/request-dto.h"
#include "config/config.h"
#include "domain/cb/cb.h"
#include "controller/request-controller.h"

RequestController::RequestController(Cb *cb, IGps *gps, ILcd *lcd, Preferences *preferences, Timer *timer)
{
    this->cb = cb;

    this->lcd = lcd;

    this->_doseUseCase = DoseUseCase(cb, this->lcd);

    this->_getGpsLocationUseCase = GetGpsLocationUseCase(gps, cb, this->lcd);

    this->_renameUseCase = RenameUseCase(lcd, cb, preferences, timer);

    this->_systematicDosesApplied = 0;
};

RequestController::RequestController()
{
    this->_systematicDosesApplied = 0;
};

pair<ResponseDto, ERROR_TYPE *> RequestController::execute(RequestDto requestDto)
{

    // loggerInfo("RequestController.execute", "Process started", "cbId: " + this->cb->id);

    if (this->_systematicError != nullptr)
    {
        ResponseDto responseDto(*cb, this->_gpsData, this->_systematicError->errorCode);
        this->_systematicError = nullptr;
        return make_pair(responseDto, this->_systematicError);
    }

    RequestModel requestModel(requestDto);
    this->cb->setRequestModel(requestModel);

    bool doseRequest = requestModel.getDose() != CONFIG_PROTOCOL_DO_NOT_DOSE;
    bool renameRequest = requestModel.getNewId()[0] != CONFIG_PROTOCOL_DO_NOT_RENAME &&
                         requestModel.getNewId()[1] != CONFIG_PROTOCOL_DO_NOT_RENAME;

    this->_systematicMetersBetweenDose = requestModel.getMetersBetweenDose();

    pair<string, ERROR_TYPE *> errorOrString = this->_getGpsLocationUseCase.execute();
    if (errorOrString.second != nullptr)
    {
        // loggerError("requestController.execute", "Process error", "error: " + errorOrString.second->description);
        ResponseDto responseDto(*cb, this->_gpsData, errorOrString.second->errorCode);
        return make_pair(responseDto, errorOrString.second);
    }

    this->_gpsData = errorOrString.first;

    if (renameRequest)
    {
        // loggerInfo("RequestController.execute", "Rename request detected");
        pair<bool, ERROR_TYPE *> errorOrBool = this->_renameUseCase.execute(requestModel.getNewId());
        if (errorOrBool.second != nullptr)
        {
            // loggerError("requestController.execute", "Process error", "error: " + errorOrBool.second->description);
            ResponseDto responseDto(*cb, this->_gpsData, errorOrBool.second->errorCode);
            return make_pair(responseDto, errorOrBool.second);
        }
    }

    if (doseRequest)
    {
        // loggerInfo("RequestController.execute", "Dose request detected");

        bool applicators[3] = {requestModel.getLeftApplicator(), requestModel.getCenterApplicator(), requestModel.getRightApplicator()};
        pair<bool, ERROR_TYPE *> errorOrBool = this->_doseUseCase.execute(requestModel.getDose(), applicators);
        if (errorOrBool.second != nullptr)
        {
            // loggerError("requestController.execute", "Process error", "error: " + errorOrBool.second->description);
            ResponseDto responseDto(*cb, this->_gpsData, errorOrBool.second->errorCode);
            return make_pair(responseDto, errorOrBool.second);
        }
        this->_distanceRanMeters = 0;
    };

    ResponseDto responseDto(*this->cb, this->_gpsData, asciiCharToNumber(this->_systematicDosesApplied));
    return make_pair(responseDto, nullptr);
};

ERROR_TYPE *RequestController::systematic()
{
    // loggerInfo("RequestController.execute", "Process started", "cbId: " + this->cb->id);

    if (this->_systematicMetersBetweenDose == CONFIG_PROTOCOL_DO_NOT_DOSE ||
        this->_systematicError != nullptr)
    {
        return this->_systematicError;
    }

    pair<string, ERROR_TYPE *> errorOrString = this->_getGpsLocationUseCase.execute();
    if (errorOrString.second != nullptr)
    {
        // loggerError("requestController.execute", "Process error", "error: " + errorOrString.second->description);
        return errorOrString.second;
    }

    float velocityMetersPerSecond = atof(splitStringBy(errorOrString.first, ',').at(7).c_str()) * 1.94384;

    this->_lastRequestTimeMs = this->_lastRequestTimeMs - millis();
    this->_distanceRanMeters = (this->_lastRequestTimeMs / 1000) * velocityMetersPerSecond;

    if (this->_distanceRanMeters >= this->_systematicMetersBetweenDose)
    {
        bool applicators[3] = {
            this->cb->getPoisonApplicators().at(0)->isConnected(),
            this->cb->getPoisonApplicators().at(1)->isConnected(),
            this->cb->getPoisonApplicators().at(2)->isConnected(),
        };

        pair<bool, ERROR_TYPE *> errorOrBool = this->_doseUseCase.execute(1, applicators);
        if (errorOrBool.second != nullptr)
        {
            // loggerError("requestController.execute", "Process error", "error: " + errorOrBool.second->description);
            ResponseDto responseDto(*cb, this->_gpsData, errorOrBool.second->errorCode);
            this->_systematicError = errorOrBool.second;
            return errorOrBool.second;
        }

        this->_systematicDosesApplied++;
        this->_distanceRanMeters = 0;
    }

    return nullptr;
};
