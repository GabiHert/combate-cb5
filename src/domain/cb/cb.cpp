#include <Arduino.h>
#include "domain/cb/cb.h"
#include "utils/utils.h"
#include "config/config.h"
#include "domain/model/response-model.h"
#include "domain/dto/response-dto.h"
#include "exceptions/error-type.h"

pair<bool, ERROR_TYPE *> Cb::dose(char amount, bool *applicatorsToDose)
{
    // loggerInfo("Cb.dose", "Process started");
    this->status = CONFIG_PROTOCOL_STATUS_BUSY;

    ResponseDto responseDto = ResponseDto(*this);
    ResponseModel responseModel = ResponseModel(&responseDto);

    unsigned char applicatorsToDoseAmount = 0;
    for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
        if (applicatorsToDose[i])
            applicatorsToDoseAmount++;

    for (char dose = 0; dose < amount; dose++)
    {
        // loggerInfo("Cb.dose", "Starting dose: " + to_string(amount));

        this->_lcd->setDoseStatus(dose + 1, amount);

        // loggerInfo("Cb.dose", "Starting all applicators");

        for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
        {
            if (!applicatorsToDose[i])
            {
                // loggerInfo("Cb.dose", "Skipping off applicator: " + to_string(i));
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
                // loggerError("Cb.dose", "Process error", "Time out");

                for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
                    this->_poisonApplicators.at(i)->stop();

                this->status = CONFIG_PROTOCOL_STATUS_ERROR;
                return make_pair(false, ERROR_TYPES().DOSE_PROCESS_TIME_OUT);
            }

            vector<bool> tasksDone = vector<bool>(CONFIG_POISON_APPLICATORS);

            unsigned char count = 0;
            for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
            {
                if (!applicatorsToDose[i])
                {
                    // loggerInfo("Cb.dose", "Skipping off applicator: " + to_string(i));
                    continue;
                }

                if (!tasksDone[i])
                {
                    // loggerInfo("Cb.dose", "Dose from applicator " + to_string(i) + " in process");
                    tasksDone[i] = this->_poisonApplicators[i]->readSensor();
                }

                if (tasksDone[i])
                {
                    // loggerInfo("Cb.dose", "Dose from applicator " + to_string(i) + " finished");
                    this->_poisonApplicators[i]->stop();
                    count++;
                }
            }

            if (count == applicatorsToDoseAmount)
                result = true;
        }
    }

    this->status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    return make_pair(true, nullptr);
};

vector<PoisonApplicator *> Cb::getPoisonApplicators()
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

Cb::Cb(App *app, ISystem *sys, ILcd *lcd)
{
    this->_poisonApplicators = vector<PoisonApplicator *>(CONFIG_POISON_APPLICATORS);
    this->_location = "NO_DATA";
    this->_sys = sys;
    this->_app = app;
    this->status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    this->id = app->getDeviceName();

    // todo: confirmar se a ordem esta correta
    this->_poisonApplicators[0] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_LEFT, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_LEFT, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_LEFT);       // esquerdo
    this->_poisonApplicators[1] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_CENTER, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_CENTER, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_CENTER); // central
    this->_poisonApplicators[2] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_RIGHT, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_RIGHT, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_RIGHT);    // direito
    this->_lcd = lcd;
};

Cb::Cb()
{
    this->status = CONFIG_PROTOCOL_STATUS_STAND_BY;
    this->_location = "NO_DATA";
    this->_poisonApplicators[0] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_LEFT, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_LEFT, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_LEFT);       // esquerdo
    this->_poisonApplicators[1] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_CENTER, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_CENTER, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_CENTER); // central
    this->_poisonApplicators[2] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_RIGHT, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_RIGHT, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_RIGHT);
};
