#include <Arduino.h>
#include "domain/cb/cb.h"
#include "utils/utils.h"
#include "config/config.h"
#include "exceptions/error.h"
#include "exceptions/cb-dose-error.h"
#include "domain/model/response-model.h"
#include "domain/dto/response-dto.h"

void Cb::dose(int amount)
{
    try
    {
        this->_status = CONFIG().PROTOCOL_STATUS_BUSY;
        loggerInfo("Cb.dose", "Process started");
        for (int dose = 0; dose < amount; dose++)
        {

            loggerInfo("Cb.dose", "Starting dose: " + to_string(amount));

            bool executedOnce = false;
            if (!executedOnce)
            {
                for (int i = 0; i < POISON_APPLICATORS; i++) // para cada aplicador
                {
                    if (this->_poisonApplicator[i].readSensor()) // se sensor estiver no ima
                    {
                        this->_poisonApplicator[i].spin(1); // começa a girar
                    }
                }
            }

            bool result = false;

            while (!result)
            {
                bool tasksDone[POISON_APPLICATORS];
                int count = 0;
                for (int i = 0; i < POISON_APPLICATORS; i++) // para cada aplicador
                {
                    tasksDone[i] = this->_poisonApplicator[i].readSensor(); // ve se o sensor chegou no ima
                    if (tasksDone[i])
                    { // se sensor chegou no ima, para o motor
                        loggerInfo("Cb.dose", "dose from applicator" + to_string(i) + "done");

                        this->_poisonApplicator[i].stop();
                        count++;
                    }
                }

                if (count == POISON_APPLICATORS) // se todas ja tiverem terminadas result = true
                {
                    result = true;
                }

                if (this->_app->avaliable())
                {
                    ResponseDto responseDto(this->_status, this->_wheelBoltsCount, this->gps.getLocation());
                    ResponseModel responseModel(responseDto);
                    this->_app->write(responseModel.tostring());
                }
            }

            this->_status = CONFIG().PROTOCOL_STATUS_STAND_BY;
        }

        loggerInfo("Cb.dose", "Process finished");
    }
    catch (Error err)
    {
        loggerError("cb.dose", "Process error", "error: " + err.message());
        throw CbDoseError(err.message());
    }
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
    this->_wheelBoltsCount[0] = '0';
    this->_wheelBoltsCount[1] = '0';
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
    this->_app = app;
    this->_id = app->getDeviceName();
    this->_wheelBoltsCount[0] = '0';
    this->_wheelBoltsCount[1] = '0';
    this->_poisonApplicator[0] = PoisonApplicator(CONFIG().PORT_MOTOR_A_1, CONFIG().PORT_MOTOR_B_1, CONFIG().PORT_SENSOR_APPLICATOR_1);
};

Cb::Cb()
{
    this->_wheelBoltsCount[0] = '0';
    this->_wheelBoltsCount[1] = '0';
    this->_poisonApplicator[0] = PoisonApplicator(CONFIG().PORT_MOTOR_A_1, CONFIG().PORT_MOTOR_B_1, CONFIG().PORT_SENSOR_APPLICATOR_1);
}

void Cb::setup()
{
    this->display.setupDisplay();
    this->gps.setup();
}

string Cb::getStatus() { return this->_status; }