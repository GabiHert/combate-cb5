#include "infra/validation/gprmc-protocol-validation.h"
#include "utils/utils.h"
#include "config/config.h"

bool GprmcProtocolValidation::validateStartHeader(string data)
{
    string startHeader = CONFIG_GPS_START_HEADER;
    for (unsigned char i = 0; i < startHeader.length(); i++)
    {
        if (!this->validateStartHeader(data[i], i))
            return false;
    }

    return true;
}

bool GprmcProtocolValidation::validateStartHeader(char charactere, unsigned char position)
{
    if (string(CONFIG_GPS_START_HEADER).length() - 1 < position)
        return false;
    return CONFIG_GPS_START_HEADER[position] == charactere;
}

bool GprmcProtocolValidation::validateEndHeader(char c, unsigned char position)
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
    unsigned char startPosition = data.find("*") - 1;

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
    bool result = this->validateEndHeader(data) && this->validateStartHeader(data);
    return result;
}

bool GprmcProtocolValidation::isDataReliable(string data)
{
    loggerInfo("GprmcProtocolValidation.isDataReliable", "Process started");

    unsigned char field = 1;
    for (unsigned char i = 0; i < data.length(); i++)
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
            return result;
        }
    }
    return false;
}