#ifndef DOSE_USE_CASE_H
#define DOSE_USE_CASE_H
#include "domain/cb/cb.h"
#include <iostream>
#include "infra/lcd/lcd-interface.h"
#include "exceptions/error-type.h"

class DoseUseCase
{
private:
    ILcd *lcd;
    Cb *cb;

public:
    DoseUseCase(Cb *cb, ILcd *lcd);
    DoseUseCase(){};
    pair<bool, ERROR_TYPE *> execute(char amount);
};

#endif