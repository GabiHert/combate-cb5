#include "utils/utils.h"

void Timer::setTimer(unsigned int ms)
{
    this->end = millis() + ms;
};

bool Timer::status()
{
    return millis() >= this->end ? true : false;
};

Timer::Timer()
{
}