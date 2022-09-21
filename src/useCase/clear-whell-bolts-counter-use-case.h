#ifndef CLEAR_WHELL_BOLTS_COUNTER_USE_CASE_H
#define CLEAR_WHELL_BOLTS_COUNTER_USE_CASE_H
#include "domain/cb/cb.h"
#include "types/error-or-boolean.h"

class ClearWhellBoltsCounterUseCase
{
private:
    Cb *cb;

public:
    ClearWhellBoltsCounterUseCase(Cb *cb);
    ClearWhellBoltsCounterUseCase(){};
    ErrorOrBool execute();
};

#endif