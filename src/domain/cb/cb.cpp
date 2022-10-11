#include <Arduino.h>
#include "domain/cb/cb.h"
#include "utils/utils.h"
#include "config/config.h"
#include "domain/model/response-model.h"
#include "domain/dto/response-dto.h"
#include "exceptions/exceptions.h"

ErrorOrBool Cb::dose(int amount)
{

    this->_status = CONFIG().PROTOCOL_STATUS_BUSY;
    loggerInfo("Cb.dose", "Process started");
    // TODO: e se o dosador N 3 terminar, e o 1 nao
    for (int dose = 0; dose < amount; dose++)
    {

        loggerInfo("Cb.dose", "Starting dose: " + to_string(amount));

        bool executedOnce = false;
        if (!executedOnce)
        {
            for (int i = 0; i < POISON_APPLICATORS; i++)
            {
                if (this->_poisonApplicator[i].readSensor())
                {
                    this->_poisonApplicator[i].spin(1);
                }
            }
        }

        bool result = false;
        Timer timer;
        timer.setTimer(CONFIG().DOSE_APPLICATION_TIMEOUT);

        while (!result)
        {
            if (timer.timedOut())
            {
                loggerError("Cb.dose", "Process error", "Time out");
                return ErrorOrBool(EXCEPTIONS().DOSE_PROCESS_TIME_OUT);
            }

            bool tasksDone[POISON_APPLICATORS];
            int count = 0;
            for (int i = 0; i < POISON_APPLICATORS; i++)
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

            if (count == POISON_APPLICATORS)
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

        this->_status = CONFIG().PROTOCOL_STATUS_STAND_BY;
    }

    loggerInfo("Cb.dose", "Process finished");
    return ErrorOrBool(true);
};

string Cb::getId()
{
    return this->_id;
};

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

Cb::Cb(App *app)
{
    this->_location = "NO_DATA"; // TODO: qual seria o valor defoult para a string do gps
    this->_app = app;
    this->_status = CONFIG().PROTOCOL_STATUS_STAND_BY;
    this->_id = app->getDeviceName();
    this->_wheelBoltsCount[0] = 0;
    this->_wheelBoltsCount[1] = 0;
    this->_poisonApplicator[0] = PoisonApplicator(CONFIG().PORT_MOTOR_A_1, CONFIG().PORT_MOTOR_B_1, CONFIG().PORT_SENSOR_APPLICATOR_1);
};

Cb::Cb()
{
    this->_status = CONFIG().PROTOCOL_STATUS_STAND_BY;
    this->_location = "NO_DATA";
    this->_wheelBoltsCount[0] = 0;
    this->_wheelBoltsCount[1] = 0;
    this->_poisonApplicator[0] = PoisonApplicator(CONFIG().PORT_MOTOR_A_1, CONFIG().PORT_MOTOR_B_1, CONFIG().PORT_SENSOR_APPLICATOR_1);
}

void Cb::setup()
{
    this->display.setupDisplay();
}

string Cb::getStatus() { return this->_status; }
