#include <Arduino.h>
#include "domain/cb/cb.h"
#include "utils/utils.h"
#include "config/config.h"
#include "exceptions/error.h"
#include "exceptions/cb-dose-error.h"

void Cb::dose()
{
    try
    {
        loggerInfo("Cb.dose", "Process started");
        Timer timer;
        timer.setTimer(200);
        if (!this->poisonApplicator[0].readSensor())
        {
            do
            {

                this->poisonApplicator[0].spin(CONFIG().SPIN_DIRECTION_CLOCKWISE);

            } while (!this->poisonApplicator[0].readSensor() || !timer.status());
        }

        this->poisonApplicator[0].stop();

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
    return this->poisonApplicator;
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

Cb::Cb(string id)
{
    this->_id = id;
    this->_wheelBoltsCount[0] = '0';
    this->_wheelBoltsCount[1] = '0';
    this->poisonApplicator[0] = PoisonApplicator(CONFIG().PORT_MOTOR_A_1, CONFIG().PORT_MOTOR_B_1, CONFIG().PORT_SENSOR_APPLICATOR_1);
};

Cb::Cb()
{
    this->_wheelBoltsCount[0] = '0';
    this->_wheelBoltsCount[1] = '0';
    this->poisonApplicator[0] = PoisonApplicator(CONFIG().PORT_MOTOR_A_1, CONFIG().PORT_MOTOR_B_1, CONFIG().PORT_SENSOR_APPLICATOR_1);
}

void Cb::setup()
{
    this->display.setupDisplay();
    this->gps.setup();
}