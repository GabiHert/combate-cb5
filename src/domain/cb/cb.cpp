#include <Arduino.h>
#include "domain/cb/cb.h"
#include "utils/utils.h"
#include "config/config.h"
#include "domain/model/response-model.h"
#include "domain/dto/response-dto.h"
#include "exceptions/exceptions.h"

ErrorOrBool Cb::dose(char amount)
{
    loggerInfo("Cb.dose", "Process started");
    // this->_status = CONFIG_PROTOCOL_STATUS_BUSY;
    int connectedApplicators = int(this->_connectedApplicators.getBoolVector().size());
    for (char dose = 0; dose < amount; dose++)
    {

        loggerInfo("Cb.dose", "Starting dose: " + to_string(amount));

        bool executedOnce = false;
        if (!executedOnce)
        {
            for (int i = 0; i < connectedApplicators; i++)
            {
                if (this->_connectedApplicators.getBoolVector()[i])
                {

                    if (this->_poisonApplicator[i].readSensor())
                    {
                        this->_poisonApplicator[i].spin();
                    }
                }
            }
        }

        bool result = false;
        Timer timer;
        timer.setTimer(CONFIG_DOSE_APPLICATION_TIMEOUT);

        while (!result)
        {
            if (timer.timedOut())
            {
                loggerError("Cb.dose", "Process error", "Time out");
                return ErrorOrBool(EXCEPTIONS().DOSE_PROCESS_TIME_OUT);
            }

            vector<bool> tasksDone = vector<bool>(CONFIG_POISON_APPLICATORS);

            int count = 0;
            for (int i = 0; i < connectedApplicators; i++)
            {
                if (this->_connectedApplicators.getBoolVector()[i])
                {
                    if (!tasksDone[i])
                        tasksDone[i] = this->_poisonApplicator[i].readSensor();

                    if (tasksDone[i])
                    {
                        loggerInfo("Cb.dose", "dose from applicator" + to_string(i) + "done");

                        this->_poisonApplicator[i].stop();
                        count++;
                    }
                }
            }

            if (count == connectedApplicators)
            {
                result = true;
            }

            if (this->_app->avaliable())
            {
                ResponseDto responseDto(this->_status, this->_wheelBoltsCount, this->_location);
                ResponseModel responseModel(responseDto);
                this->_app->write(responseModel.toString());
            }
        }

        this->_status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    }

    loggerInfo("Cb.dose", "Process finished");
    return ErrorOrBool(true);
};

string Cb::getId()
{
    return this->_id;
};

string Cb::getStatus() { return this->_status; };
ErrorOrBoolVector Cb::getConnectedApplicators()
{
    return this->_connectedApplicators;
}

PoisonApplicator *Cb::getPoisonApplicator()
{
    return this->_poisonApplicator;
};

char Cb::getWhellBoltsCountDecimal()
{
    return this->_wheelBoltsCount[0];
};
char Cb::getWhellBoltsCountUnit()
{
    return this->_wheelBoltsCount[1];
};

void Cb::clearWhellBoltsCount()
{
    this->_wheelBoltsCount[0] = 0;
    this->_wheelBoltsCount[1] = 0;
};

void Cb::addWhellBoltsCount()
{
    // TODO: Implemetar logica
    //  add somente ate 99
}

void Cb::setRequestModel(RequestModel requestModel)
{
    this->requestModel = requestModel;
};

RequestModel Cb::getRequestModel()
{
    return this->requestModel;
};

Cb::Cb(App *app, ISystem *sys)
{
    this->_location = "NO_DATA";
    this->_sys = sys;
    this->_app = app;
    this->_status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    this->_id = app->getDeviceName();
    this->_wheelBoltsCount[0] = 0;
    this->_wheelBoltsCount[1] = 0;
    this->_poisonApplicator[0] = PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_1, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_1);
    this->_poisonApplicator[1] = PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_2, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_2);
    this->_poisonApplicator[2] = PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_3, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_3);
    this->updateConnectedApplicators();
};

Cb::Cb()
{
    this->_status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    this->_location = "NO_DATA";
    this->_wheelBoltsCount[0] = 0;
    this->_wheelBoltsCount[1] = 0;
    this->_poisonApplicator[0] = PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_1, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_1);
    this->_poisonApplicator[0] = PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_2, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_2);
    this->_poisonApplicator[0] = PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_3, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_3);
    this->updateConnectedApplicators();
};

ErrorOrInt Cb::updateConnectedApplicators()
{
    loggerInfo("Cb.updateConnectedApplicators", "Process started");
    int applicators = 0;
    for (int i = 0; i < CONFIG_POISON_APPLICATORS; i++)
    {
        if (this->_sys->readDigitalPort(CONFIG().PORT_GPIO_SENSOR_CONNECTED_APPLICATORS[i]) > 0)
        {
            loggerInfo("Cb.updateConnectedApplicators", "Applicator found");

            applicators++;
            this->_connectedApplicators.getBoolVector().push_back(true);
        }
        else
        {
            loggerInfo("Cb.updateConnectedApplicators", "Empty slot");

            this->_connectedApplicators.getBoolVector().push_back(false);
        }
    }
    if (!applicators)
    {
        loggerError("Cb.updateConnectedApplicators", "Process error", "applicators: " + to_string(applicators));
        this->_connectedApplicators = ErrorOrBoolVector(EXCEPTIONS().NO_APPLICATORS_FOUND_ERROR);
        return ErrorOrInt(EXCEPTIONS().NO_APPLICATORS_FOUND_ERROR);
    }

    loggerInfo("Cb.updateConnectedApplicators", "Process finished", "applicators: " + to_string(applicators));
    return ErrorOrInt(applicators);
}