#include "infra/validation/gprmc-protocol-validation.h"
#include "utils/utils.h"
#include "config/config.h"

bool GprmcProtocolValidation::validateStartHeader(string data)
{
    string startHeader = CONFIG_GPS_START_HEADER;
    for (int i = 0; i < startHeader.length(); i++)
    {
        if (!this->validateStartHeader(data[i], i))
            return false;
    }

    return true;
}

bool GprmcProtocolValidation::validateStartHeader(char charactere, int position)
{
    if (string(CONFIG_GPS_START_HEADER).length() - 1 < position)
        return false;
    return CONFIG_GPS_START_HEADER[position] == charactere;
}

bool GprmcProtocolValidation::validateEndHeader(char c, int position)
{

    switch (position)
    {
    case 0:
        return c == 'A' || c == 'D' || c == 'E' || c == 'M' || c == 'N';
        break;

    case 1:
        return c == '*';
        break;

    case 2:
        return asciiCharToNumber(c) > 0;
        break;

    case 3:
        return asciiCharToNumber(c) > 0;
        break;

    default:
        return false;
        break;
    }
}

bool GprmcProtocolValidation::validateEndHeader(string data)
{
    int startPosition = data.find("*") - 1;

    if (this->validateEndHeader(data[startPosition], 0) &&
        this->validateEndHeader(data[startPosition + 1], 1) &&
        this->validateEndHeader(data[startPosition + 2], 2) &&
        this->validateEndHeader(data[startPosition + 3], 3))
    {
        return true;
    }

    return false;
}

bool GprmcProtocolValidation::validate(string data)
{
    loggerInfo("GprmcProtocolValidation.validate", "Process started", data);

    bool result = this->validateEndHeader(data) && this->validateStartHeader(data);

    loggerInfo("GprmcProtocolValidation.validate", "Process finished", "result: " + to_string(result));
    return result;
}

bool GprmcProtocolValidation::isDataReliable(string data)
{
    loggerInfo("GprmcProtocolValidation.isDataReliable", "Process finished");

    int field = 1;
    for (int i = 0; i < data.length(); i++)
    {

        if (field > 3)
            break;

        if (data[i] == ',')
        {
            field++;
        }

        if (field == 3)
        {
            bool result = data[i + 1] == 'A';
            loggerInfo("GprmcProtocolValidation.isDataReliable", "Process finished", "result: " + to_string(result));

            return result;
        }
    }
    loggerInfo("GprmcProtocolValidation.isDataReliable", "Process finished", "result:  0");
    return false;
}