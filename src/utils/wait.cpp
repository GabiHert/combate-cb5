#include "utils/utils.h"

void Timer::setTimer(unsigned long ms)
{
    this->end = millis() + ms;
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
    if (millis() >= this->end ){
        this->end=1;
        return  true;
    }else{
        return false;
    }
    
};

Timer::Timer()
{
    this->end = 0;
}