#ifndef DOSE_USE_CASE_H
#define DOSE_USE_CASE_H
#include "domain/cb/cb.h"

class DoseUseCase
{
private:
    Cb *cb;

public:
    DoseUseCase(Cb *cb);
    DoseUseCase(){};
    void execute(int amount);
};

#endif