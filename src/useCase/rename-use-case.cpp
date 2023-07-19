#include "utils/utils.h"
#include "exceptions/exceptions.h"
#include "useCase/rename-use-case.h"

RenameUseCase::RenameUseCase(Preferences *preferences, Cb *cb)
{
    this->_cb = cb;
    this->_preferences = preferences;
};

ErrorOrBool RenameUseCase::execute(string name)
{
    loggerInfo("RenameUseCase", "Process started", "name: " + name);
    bool result = this->_preferences->remove(CONFIG_PREFERENCES_DEVICE_NAME_KEY);
    if (!result)
    {
        return ErrorOrBool(EXCEPTIONS().RENAME_ERROR);
    }
    result = this->_preferences->putString(
        CONFIG_PREFERENCES_DEVICE_NAME_KEY,
        name.c_str());

    if (!result)
    {
        return ErrorOrBool(EXCEPTIONS().RENAME_ERROR);
    }

    this->_cb->setId(name);

    this->_lcd->clear();
    this->_lcd->setCursor(0, 0);
    this->_lcd->printCentered(name);

    Timer timer;
    timer.setTimer(5000)->wait();

    this->_lcd->clear();
    this->_lcd->setCursor(0, 0);
    this->_lcd->printCentered("REINICIE O CB5");

    timer.setTimer(5000)->wait();
    loggerInfo("RenameUseCase", "Process finished");

    return ErrorOrBool(true);
};