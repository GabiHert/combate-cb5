#ifndef RENAME_USE_CASE_H
#define RENAME_USE_CASE_H
#include "domain/cb/cb.h"
#include "domain/model/request-model.h"
#include "types/error-or-boolean.h"
#include "infra/lcd/lcd-interface.h"

class RenameUseCase
{
private:
    ILcd *_lcd;
    Cb *_cb;
    Preferences *_preferences;

public:
    RenameUseCase(Preferences *preferences, Cb *cb);
    RenameUseCase(){};
    ErrorOrBool execute(string name);
};

#endif