
#include "useCase/rename-use-case.h"
#include "utils/utils.h"
#include "config/config.h"

RenameUseCase::RenameUseCase(ILcd *lcd, Cb *cb, Preferences *preferences, Timer *timer)
{
    this->_lcd = lcd;
    this->_timer = timer;
    this->_cb = cb;
    this->_preferences = preferences;
};

pair<bool, ERROR_TYPE *> RenameUseCase::execute(char *newId)
{
    //loggerInfo("RenameUsCase", "Process started", "newId: " + newId[0] + newId[1]);

    string newName = "CB5_";
    newName += newId[0];
    newName += newId[1];

    this->_preferences->putString(CONFIG_PREFERENCES_DEVICE_NAME_KEY, stdStringToArduinoString(newName));

    string name = this->_preferences->getString(CONFIG_PREFERENCES_DEVICE_NAME_KEY).c_str();

    if (name != newName)
    {
        this->_cb->status = CONFIG_PROTOCOL_STATUS_ERROR;
        return make_pair(false, ERROR_TYPES().RENAME_ERROR);
    }

    this->_lcd->clear();
    this->_lcd->printCentered("CB RENOMEADO", 0, 0);
    this->_lcd->printCentered(newName, 0, 1);
    this->_timer->setTimer(2000)->wait();

    this->_cb->id = newName;

    return make_pair(true, nullptr);
};