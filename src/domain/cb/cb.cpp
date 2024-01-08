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

    unsigned char applicatorsToDoseAmount = 0;
    for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
    {
        if (applicatorsToDose[i])
        {
            // loggerInfo("Cb.dose", "Applicator " + to_string(i) + " should dose");
            applicatorsToDoseAmount++;
        }
    }

    for (char dose = 0; dose < amount; dose++)
    {
        // loggerInfo("Cb.dose", "Starting dose: " + to_string(amount));

        this->_lcd->setDoseStatus(dose + 1, amount);

        // loggerInfo("Cb.dose", "Starting all applicators");
        unsigned long startTime = millis();

        for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
        {
            if (!applicatorsToDose[i])
            {
                // loggerInfo("Cb.dose", "Skipping off applicator: " + to_string(i));
                continue;
            }

            this->_poisonApplicators[i]->spin();

            this->_timer->setTimer(100);
            this->_timer->wait();
        }

        this->_timer->setTimer(CONFIG_DOSE_APPLICATION_TIMEOUT);

        unsigned char count = 0;

        bool applicatorsToDoseAux[CONFIG_POISON_APPLICATORS] = {
            applicatorsToDose[0],
            applicatorsToDose[1],
            applicatorsToDose[2],
        };

        while (count < applicatorsToDoseAmount)
        {

            if (this->_timer->timedOut())
            {
                // loggerError("Cb.dose", "Process error", "Time out");

                for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
                    this->_poisonApplicators.at(i)->stop();

                return make_pair(false, ERROR_TYPES().DOSE_PROCESS_TIME_OUT);
            }

            vector<bool> tasksDone = vector<bool>(CONFIG_POISON_APPLICATORS);

            for (unsigned char i = 0; i < CONFIG_POISON_APPLICATORS; i++)
            {
                if (!applicatorsToDoseAux[i])
                {
                    // loggerInfo("Cb.dose", "Skipping off or finished applicator: " + to_string(i));
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
                    if (millis() - startTime < CONFIG_DOSE_MIN_DURATION_MILLISECONDS)
                    {
                        // loggerError("Cb.dose", "Process error", "Time out (too fast)");
                        return make_pair(false, ERROR_TYPES().DOSE_PROCESS_TIME_OUT);
                    }

                    applicatorsToDoseAux[i] = false;
                    this->_poisonApplicators[i]->stop();
                    count++;
                }
            }

            // loggerInfo("Cb.dose", "count: " + to_string(count) + " totalToDose: " + to_string(applicatorsToDoseAmount));
        }
        // loggerInfo("Cb.dose", "dosesApplied: " + to_string(dose) + " target: " + to_string(amount));
    }

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

Cb::Cb(App *app, ISystem *sys, ILcd *lcd, Timer *timer)
{
    this->_timer = timer;
    this->_poisonApplicators = vector<PoisonApplicator *>(CONFIG_POISON_APPLICATORS);
    this->_sys = sys;
    this->_app = app;
    this->id = app->getDeviceName();

    this->_poisonApplicators[0] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_LEFT, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_LEFT, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_LEFT);       // esquerdo
    this->_poisonApplicators[1] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_CENTER, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_CENTER, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_CENTER); // central
    this->_poisonApplicators[2] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_RIGHT, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_RIGHT, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_RIGHT);    // direito
    this->_lcd = lcd;
};

Cb::Cb()
{
    this->_poisonApplicators[0] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_LEFT, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_LEFT, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_LEFT);       // esquerdo
    this->_poisonApplicators[1] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_CENTER, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_CENTER, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_CENTER); // central
    this->_poisonApplicators[2] = new PoisonApplicator(this->_sys, CONFIG_PORT_GPIO_MOTOR_RIGHT, CONFIG_PORT_GPIO_SENSOR_APPLICATOR_RIGHT, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_RIGHT);
};
