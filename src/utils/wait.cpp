#include "utils/utils.h"

Timer *Timer::setTimer(unsigned long ms)
{
    this->end = millis() + ms;
    return this;
};

void Timer::wait()
{
    if (this->end == 1)
        return;

    while (!this->timedOut())
    {
    }
}

bool Timer::timedOut()
{
    return millis() >= this->end ? true : false;
};

Timer::Timer()
{
    this->end = 0;
}