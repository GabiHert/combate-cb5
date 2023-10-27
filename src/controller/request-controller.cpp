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

    this->_systematicError = nullptr;

    this->_endTime = 0;

    this->_lastCommunicationTimeMs = 0;

    this->_systematicMetersBetweenDoseParsed = 0;

    this->_systematicDosesApplied = 0;

    this->_systematicMetersBetweenDose = CONFIG_PROTOCOL_DO_NOT_DOSE;
};

RequestController::RequestController()
{
    this->_endTime = 0;
    this->_lastCommunicationTimeMs = 0;
    this->_systematicMetersBetweenDose = CONFIG_PROTOCOL_DO_NOT_DOSE;
    this->_systematicMetersBetweenDoseParsed = 0;
    this->_systematicDosesApplied = 0;
    this->_systematicError = nullptr;
};

pair<ResponseDto, ERROR_TYPE *> RequestController::execute(RequestDto requestDto)
{

    // loggerInfo("RequestController.execute", "Process started", "cbId: " + this->cb->id);

    this->_lastCommunicationTimeMs = millis();

    if (this->_systematicError != nullptr)
    {
        // loggerInfo("RequestController.execute", "systematicError");

        ResponseDto responseDto(*cb, this->_gpsData, this->_systematicError->errorCode);
        this->_systematicError = nullptr;
        return make_pair(responseDto, this->_systematicError);
    }

    // loggerInfo("RequestController.execute", "no error");

    RequestModel requestModel(requestDto);
    this->cb->setRequestModel(requestModel);

    bool doseRequest = requestModel.getDose() != CONFIG_PROTOCOL_DO_NOT_DOSE;
    bool renameRequest = requestModel.getNewId()[0] != CONFIG_PROTOCOL_DO_NOT_RENAME &&
                         requestModel.getNewId()[1] != CONFIG_PROTOCOL_DO_NOT_RENAME;

    this->_systematicMetersBetweenDose = requestModel.getMetersBetweenDose();

    if (this->_systematicMetersBetweenDoseParsed != CONFIG_PROTOCOL_DO_NOT_DOSE)
    {
        this->_systematicMetersBetweenDoseParsed = asciiCharToNumber(this->_systematicMetersBetweenDose);
    }

    pair<string, ERROR_TYPE *> errorOrString = this->_getGpsLocationUseCase.execute();
    if (errorOrString.second != nullptr)
    {
        //  loggerError("requestController.execute", "Process error", "error: " + errorOrString.second->description);
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
        this->_endTime = this->_lastCommunicationTimeMs;
    };

    ResponseDto responseDto(*this->cb, this->_gpsData, numberToProtocolNumber(this->_systematicDosesApplied));
    this->_systematicDosesApplied = 0;
    return make_pair(responseDto, nullptr);
};

ERROR_TYPE *RequestController::systematic()
{
    // loggerInfo("RequestController.systematic", "Process started");

    unsigned long startTime = millis();

    this->lcd->setSystematicMetersBetweenDose(this->_systematicMetersBetweenDose);

    if (startTime - this->_lastCommunicationTimeMs > CONFIG_COMMUNICATION_WAIT_ACCEPTANCE_MS)
    {
        this->_systematicMetersBetweenDose = CONFIG_PROTOCOL_DO_NOT_DOSE;
    }

    if (this->_systematicMetersBetweenDose == CONFIG_PROTOCOL_DO_NOT_DOSE)
    {
        // loggerInfo("RequestController.systematic", "CONFIG_PROTOCOL_DO_NOT_DOSE");
        return nullptr;
    }

    if (this->_systematicError != nullptr)
    {
        // loggerInfo("RequestController.systematic", "ERROR");
        return this->_systematicError;
    }

    pair<string, ERROR_TYPE *> errorOrString = this->_getGpsLocationUseCase.execute();
    if (errorOrString.second != nullptr)
    {
        //  loggerError("requestController.systematic", "Process error", "error: " + errorOrString.second->description);
        return errorOrString.second;
    }

    float velocityMetersPerSecond = atof(splitStringBy(errorOrString.first, ',').at(6).c_str()) * 1.94384;

    // loggerInfo("requestController.systematic", "Velocity", to_string(velocityMetersPerSecond));
    // loggerInfo("requestController.systematic", "GPS", errorOrString.first);

    unsigned long elapsedTimeMs = startTime - this->_endTime;

    // loggerInfo("RequestController.systematic", "_lastDoseTimeMs: " + to_string(this->_lastDoseTimeMs));
    // loggerInfo("RequestController.systematic", "elapsedTimeMs: " + to_string(elapsedTimeMs));

    this->_distanceRanMeters += (elapsedTimeMs / 1000) * velocityMetersPerSecond;

    if (this->_distanceRanMeters >= this->_systematicMetersBetweenDoseParsed)
    {
        // loggerInfo("RequestController.systematic", "_distanceRanMeters: " + to_string(this->_distanceRanMeters) + " this->_systematicMetersBetweenDoseParsed: " + to_string(this->_systematicMetersBetweenDoseParsed));

        bool applicators[3] = {
            this->cb->getPoisonApplicators().at(0)->isConnected(),
            this->cb->getPoisonApplicators().at(1)->isConnected(),
            this->cb->getPoisonApplicators().at(2)->isConnected(),
        };

        pair<bool, ERROR_TYPE *> errorOrBool = this->_doseUseCase.execute('1', applicators);
        if (errorOrBool.second != nullptr)
        {
            // loggerError("requestController.systematic", "Process error", "error: " + errorOrBool.second->description);
            ResponseDto responseDto(*cb, this->_gpsData, errorOrBool.second->errorCode);
            this->_systematicError = errorOrBool.second;
            return errorOrBool.second;
        }
        this->_systematicDosesApplied++;
        this->_distanceRanMeters = 0;
    }

    this->_endTime = millis();

    return nullptr;
};
