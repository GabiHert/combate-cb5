#include <Arduino.h>
#include "domain/cb/cb.h"
#include "utils/utils.h"
#include "config/config.h"
#include "domain/model/response-model.h"
#include "domain/dto/response-dto.h"
#include "exceptions/error-type.h"

pair<bool, ERROR_TYPE *> Cb::dose(char amount)
{
    loggerInfo("Cb.dose", "Process started");
    this->_status = CONFIG_PROTOCOL_STATUS_BUSY;

    ResponseDto responseDto = ResponseDto(*this);
    ResponseModel responseModel = ResponseModel(responseDto);
    string responseString = responseModel.toString();
    string separator;
    for (unsigned char i = 0; i < CONFIG_GPS_MESSAGE_LENGTH - (responseString.length() - 12); i++)
        separator += "-";

    this->_app->write(responseString);
    this->_app->write(separator);

    unsigned char connectedApplicators = 0;
    for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
        if (this->_applicators.first[i])
            connectedApplicators++;

    for (char dose = 0; dose < amount; dose++)
    {
        loggerInfo("Cb.dose", "Starting dose: " + to_string(amount));

        this->_lcd->setDoseStatus(dose + 1, amount);

        loggerInfo("Cb.dose", "Starting all applicators");

        for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
        {
            bool isApplicatorConnected = this->_applicators.first[i];
            if (!isApplicatorConnected)
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

                for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
                    this->_poisonApplicators.at(i)->stop();

                this->_status = CONFIG_PROTOCOL_STATUS_ERROR;
                return make_pair(false, ERROR_TYPES().DOSE_PROCESS_TIME_OUT);
            }

            vector<bool> tasksDone = vector<bool>(CONFIG_POISON_APPLICATORS);

            unsigned char count = 0;
            for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
            {
                bool isApplicatorConnected = this->_applicators.first[i];
                if (!isApplicatorConnected)
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

            if (count == connectedApplicators)
                result = true;
        }
    }

    this->_status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    return make_pair(true, nullptr);
};

string Cb::getId()
{
    return this->_id;
};

string Cb::getStatus() { return this->_status; };
pair<vector<bool>, ERROR_TYPE *> Cb::getApplicators()
{
    return this->_applicators;
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

unsigned char Cb::getConnectedApplicators()
{
    return this->_connectedApplicators;
}

Cb::Cb(App *app, ISystem *sys, ILcd *lcd)
{
    this->_poisonApplicators = vector<PoisonApplicator *>(CONFIG_POISON_APPLICATORS);
    this->_connectedApplicators = 0;
    this->_location = "NO_DATA";
    this->_sys = sys;
    this->_app = app;
    this->_status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    this->_id = app->getDeviceName();

    this->_poisonApplicators[0] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_1, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_1);
    this->_poisonApplicators[1] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_2, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_2);
    this->_poisonApplicators[2] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_3, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_3);
    this->updateConnectedApplicators();
    this->_lcd = lcd;
};

Cb::Cb()
{
    this->_connectedApplicators = 0;
    this->_status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    this->_location = "NO_DATA";
    this->_poisonApplicators[0] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_1, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_1);
    this->_poisonApplicators[0] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_2, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_2);
    this->_poisonApplicators[0] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_3, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_3);
    this->updateConnectedApplicators();
};

pair<int, ERROR_TYPE *> Cb::updateConnectedApplicators()
{
    loggerInfo("Cb.updateConnectedApplicators", "Process started");
    this->_connectedApplicators = 0;
    vector<bool> applicatorsConnection = vector<bool>(CONFIG_POISON_APPLICATORS);
    for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
    {
        if (!this->_sys->readDigitalPort(CONFIG().PORT_GPIO_SENSOR_CONNECTED_APPLICATORS[i]))
        {
            loggerInfo("Cb.updateConnectedApplicators", "Applicator found");

            this->_connectedApplicators++;
            applicatorsConnection.at(i) = true;
        }
        else
        {
            loggerInfo("Cb.updateConnectedApplicators", "Empty slot");

            applicatorsConnection.at(i) = false;
        }
    }
    if (!this->_connectedApplicators)
    {
        loggerError("Cb.updateConnectedApplicators", "Process error", "applicators: " + to_string(this->_connectedApplicators));
        this->_applicators = make_pair(vector<bool>(), ERROR_TYPES().NO_APPLICATORS_FOUND_ERROR);
        return make_pair(0, ERROR_TYPES().NO_APPLICATORS_FOUND_ERROR);
    }
    this->_applicators = make_pair(applicatorsConnection, nullptr);

    return make_pair(this->_connectedApplicators, nullptr);
}

void Cb::clearStatus()
{
    this->_status = CONFIG_PROTOCOL_STATUS_STAND_BY;
}