#ifndef DOSE_USE_CASE_H
#define DOSE_USE_CASE_H
#include "domain/cb/cb.h"
#include "types/error-or-boolean.h"
#include "infra/lcd/lcd-interface.h"

class DoseUseCase
{
private:
    IDisplay *display;
    Cb *cb;

public:
    DoseUseCase(Cb *cb, IDisplay *display);
    DoseUseCase(){};
    ErrorOrBool execute(char amount);
};

#endif