#ifndef CLEAR_WHEEL_BOLTS_COUNTER_USE_CASE_H
#define CLEAR_WHEEL_BOLTS_COUNTER_USE_CASE_H
#include "domain/cb/cb.h"
#include "types/error-or-boolean.h"

class ClearWheelBoltsCounterUseCase
{
private:
    Cb *cb;

public:
    ClearWheelBoltsCounterUseCase(Cb *cb);
    ClearWheelBoltsCounterUseCase(){};
    ErrorOrBool execute();
};

#endif