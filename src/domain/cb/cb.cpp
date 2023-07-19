#include <Arduino.h>
#include "domain/cb/cb.h"
#include "utils/utils.h"
#include "config/config.h"
#include "domain/model/response-model.h"
#include "domain/dto/response-dto.h"
#include "exceptions/exceptions.h"

ErrorOrBool Cb::dose(char amount, vector<bool> applicators)
{
    loggerInfo("Cb.dose", "Process started");
    this->_status = CONFIG_PROTOCOL_STATUS_BUSY;

    ResponseDto responseDto = ResponseDto(*this);
    ResponseModel responseModel = ResponseModel(responseDto);
    string responseString = responseModel.toString();

    this->_app->write(responseString);

    int applicatorsToDose = 0;
    for (int i = 0; i < CONFIG_POISON_APPLICATORS; i++)
        if (applicators[i])
            applicatorsToDose++;

    for (char dose = 0; dose < amount; dose++)
    {
        loggerInfo("Cb.dose", "Starting dose: " + to_string(amount));

        this->_lcd->setDoseStatus(dose + 1, amount);

        loggerInfo("Cb.dose", "Starting all applicators");

        for (int i = 0; i < CONFIG_POISON_APPLICATORS; i++)
        {
            bool shouldDose = applicators[i];
            if (!shouldDose)
            {
                loggerInfo("Cb.dose", "Skipping off applicator: " + to_string(i));
                continue;
            }
            this->_poisonApplicators[i]->spin();
        }

        bool result = false;
        Timer timer;
        timer.setTimer(200);
        timer.wait();

        timer.setTimer(CONFIG_DOSE_APPLICATION_TIMEOUT);

        while (!result)
        {
            if (timer.timedOut())
            {
                loggerError("Cb.dose", "Process error", "Time out");

                for (int i = 0; i < CONFIG_POISON_APPLICATORS; i++)
                    this->_poisonApplicators.at(i)->stop();

                this->_status = CONFIG_PROTOCOL_STATUS_ERROR;
                return ErrorOrBool(EXCEPTIONS().DOSE_PROCESS_TIME_OUT);
            }

            vector<bool> tasksDone = vector<bool>(CONFIG_POISON_APPLICATORS);

            int count = 0;
            for (int i = 0; i < CONFIG_POISON_APPLICATORS; i++)
            {
                bool shouldDose = applicators[i];
                if (!shouldDose)
                {
                    loggerInfo("Cb.dose", "Skipping off applicator: " + to_string(i));
                    continue;
                }

                if (!tasksDone[i])
                {
                    loggerInfo("Cb.dose", "Dose from applicator " + to_string(i) + " in process");
                    tasksDone[i] = this->_poisonApplicators[i]->readSensor();
                }

                if (tasksDone[i])
                {
                    loggerInfo("Cb.dose", "Dose from applicator " + to_string(i) + " finished");
                    this->_poisonApplicators[i]->stop();
                    count++;
                }
            }

            if (count == applicatorsToDose)
                result = true;
        }
    }

    this->_status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    loggerInfo("Cb.dose", "Process finished");
    return ErrorOrBool(true);
};

string Cb::getId()
{
    return this->_id;
};

void Cb::setId(string id)
{
    this->_id = id;
}
string Cb::getStatus()
{
    return this->_status;
};

ErrorOrBoolVector Cb::getConnectedApplicators()
{
    return this->_connectedApplicators;
}

vector<PoisonApplicator *> Cb::getPoisonApplicator()
{
    return this->_poisonApplicators;
};

void Cb::setRequestModel(RequestModel requestModel)
{
    this->requestModel = requestModel;
};

RequestModel Cb::getRequestModel()
{
    return this->requestModel;
};

int Cb::getConnectedApplicatorsAmount()
{
    return this->_connectedApplicatorsAmount;
}

Cb::Cb(App *app, ISystem *sys, ILcd *lcd)
{
    this->_poisonApplicators = vector<PoisonApplicator *>(CONFIG_POISON_APPLICATORS);
    this->_connectedApplicatorsAmount = 0;
    this->_location = "NO_DATA";
    this->_sys = sys;
    this->_app = app;
    this->_status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    this->_id = app->getDeviceName();
    this->_wheelBoltsCount[0] = 0;
    this->_wheelBoltsCount[1] = 0;
    this->_poisonApplicators[0] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_1, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_1);
    this->_poisonApplicators[1] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_2, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_2);
    this->_poisonApplicators[2] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_3, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_3);
    this->updateConnectedApplicators();
    this->_lcd = lcd;
};

Cb::Cb()
{
    this->_connectedApplicatorsAmount = 0;
    this->_status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    this->_location = "NO_DATA";
    this->_wheelBoltsCount[0] = 0;
    this->_wheelBoltsCount[1] = 0;
    this->_poisonApplicators[0] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_1, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_1);
    this->_poisonApplicators[0] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_2, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_2);
    this->_poisonApplicators[0] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_3, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_3);
    this->updateConnectedApplicators();
};

ErrorOrInt Cb::updateConnectedApplicators()
{
    loggerInfo("Cb.updateConnectedApplicators", "Process started");
    this->_connectedApplicatorsAmount = 0;
    vector<bool> applicatorsConnection = vector<bool>(CONFIG_POISON_APPLICATORS);
    for (int i = 0; i < CONFIG_POISON_APPLICATORS; i++)
    {
        if (!this->_sys->readDigitalPort(CONFIG().PORT_GPIO_SENSOR_CONNECTED_APPLICATORS[i]))
        {
            loggerInfo("Cb.updateConnectedApplicators", "Applicator found");

            this->_connectedApplicatorsAmount++;
            applicatorsConnection.at(i) = true;
        }
        else
        {
            loggerInfo("Cb.updateConnectedApplicators", "Empty slot");

            applicatorsConnection.at(i) = false;
        }
    }
    if (!this->_connectedApplicatorsAmount)
    {
        loggerError("Cb.updateConnectedApplicators", "Process error", "applicators: " + to_string(this->_connectedApplicatorsAmount));
        this->_connectedApplicators = ErrorOrBoolVector(EXCEPTIONS().NO_APPLICATORS_FOUND_ERROR);
        return ErrorOrInt(EXCEPTIONS().NO_APPLICATORS_FOUND_ERROR);
    }
    this->_connectedApplicators = ErrorOrBoolVector(applicatorsConnection);

    loggerInfo("Cb.updateConnectedApplicators", "Process finished", "applicators: " + to_string(this->_connectedApplicatorsAmount));
    return ErrorOrInt(this->_connectedApplicatorsAmount);
}

void Cb::clearStatus()
{
    loggerInfo("Cb.clearStatus", "Process started");
    this->_status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    loggerInfo("Cb.clearStatus", "Process finished");
}