
#include "useCase/rename-use-case.h"
#include "utils/utils.h"
#include "config/config.h"

RenameUseCase::RenameUseCase(ILcd *lcd, Cb *cb, Preferences *preferences)
{
    this->_lcd = lcd;
    this->_cb = cb;
    this->_preferences = preferences;
};

pair<bool, ERROR_TYPE *> RenameUseCase::execute(char *newId)
{
    loggerInfo("RenameUsCase", "Process started", "newId: " + newId[0] + newId[1]);

    String newName = "CB5_" + newId[0] + newId[1];

    this->_preferences->putString(CONFIG_PREFERENCES_DEVICE_NAME_KEY, newName);

    String name = this->_preferences->getString(CONFIG_PREFERENCES_DEVICE_NAME_KEY);

    if (name != newName)
    {
        return make_pair(false, ERROR_TYPES().RENAME_ERROR);
    }

    return make_pair(true, nullptr);
};