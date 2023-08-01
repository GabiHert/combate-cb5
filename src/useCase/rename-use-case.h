

#ifndef RENAME_USE_CASE_H
#define RENAME_USE_CASE_H

#include "domain/cb/cb.h"
#include <iostream>
#include "infra/lcd/lcd-interface.h"
#include "exceptions/error-type.h"
#include <preferences.h>

class RenameUseCase
{
private:
    ILcd *_lcd;
    Cb *_cb;
    Preferences *_preferences;

public:
    RenameUseCase(){};
    RenameUseCase(ILcd *lcd, Cb *cb, Preferences *preferences);

    pair<bool, ERROR_TYPE *> execute(char *newId);
};

#endif