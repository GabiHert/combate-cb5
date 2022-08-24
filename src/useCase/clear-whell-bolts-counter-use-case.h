#ifndef CLEAR_WHELL_BOLTS_COUNTER_USE_CASE_H
#define CLEAR_WHELL_BOLTS_COUNTER_USE_CASE_H
#include "domain/cb/cb.h"

class ClearWhellBoltsCounterUseCase
{
private:
    Cb *cb;

public:
    ClearWhellBoltsCounterUseCase(Cb *cb);
    ClearWhellBoltsCounterUseCase(){};
    void execute();
};

#endif