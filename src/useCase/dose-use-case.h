#ifndef DOSE_USE_CASE_H
#define DOSE_USE_CASE_H
#include "domain/cb/cb.h"
#include "types/error-or-boolean.h"
#include "infra/lcd/lcd-interface.h"

class DoseUseCase
{
private:
    ILcd *lcd;
    Cb *cb;

public:
    DoseUseCase(Cb *cb, ILcd *lcd);
    DoseUseCase(){};
    ErrorOrBool execute(char amount, vector<bool> applicators);
};

#endif