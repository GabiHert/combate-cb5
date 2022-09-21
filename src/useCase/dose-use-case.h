#ifndef DOSE_USE_CASE_H
#define DOSE_USE_CASE_H
#include "domain/cb/cb.h"
#include "types/error-or-boolean.h"

class DoseUseCase
{
private:
    Cb *cb;

public:
    DoseUseCase(Cb *cb);
    DoseUseCase(){};
    ErrorOrBool execute(char amount);
};

#endif