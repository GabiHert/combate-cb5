#include "utils/utils.h"

void Timer::setTimer(unsigned long ms)
{
    this->end = millis() + ms;
};

bool Timer::timedOut()
{

    return millis() >= this->end ? true : false;
};

Timer::Timer()
{
}