/*
#include "delivery/interfaces/cb5.h"
#include "utils/utils.h"
#include <Arduino.h>
#include "domain/cb/cb.h"
#include "middleware/request-middleware.h"
#include "config/config.h"
#include "interfaces/system-interface.h"
#include <string.h>
#include "domain/builder/check-sum-builder.h"
using namespace std;
#include "exceptions/validation-error.h"

App app(CONFIG_DEVICE_NAME);
Cb cb(&app);

RequestMiddleware requestMiddleware(cb);
ISystem sys;

int buildCheckSum(string data)
{
    unsigned char dataLastIndex = data.length();
    int sum = 0;
    for (int i = 0; i < dataLastIndex; i++)
    {
        sum += int(data[i]);
    };

    int CS = 256 - (sum % 256);
    loggerInfo("SERIAL CS BUILDER", "Process finished", " requestData: " + data + "; CheckSum: " + to_string(CS));

    return CS;
};

int HexDigit(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }

    if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 10;
    }

    return 0;
}

char HexByte(char *p)
{
    loggerInfo("SERIAL HEX BYTE", p);

    char value = 0;

    value += HexDigit(*p++);
    loggerInfo("SERIAL HEX BYTE", to_string(value));

    if (*p != '\0')
    {
        value = value * 16 + HexDigit(*p);
        loggerInfo("SERIAL HEX BYTE -  CAIU NO IF", to_string(value));
    }
    return value;
}
int intToAscii(int number)
{
    return '0' + number;
}

string endPointBuilder(string request)
{
    string requestData = request.substr(CONFIG_PROTOCOL_DATA_START_INDEX, CONFIG_PROTOCOL_DATA_END_INDEX);

    CheckSumBuilder csBuilder;
    string cs;

    cs += csBuilder.build(requestData);

    string endPoint = cs;

    endPoint += '\r';
    endPoint += '\n';

    for (int i = 0; i < endPoint.length(); i++)
    {
        sys.serialPrintln("END POINT index " + to_string(i));
        sys.serialPrintln(to_string((int)endPoint[i]));
    }
    return endPoint;
}

void CB5::setup()
{
    cb.setup();
    Serial.begin(CONFIG_SERIAL_BAUD_RATE);

    loggerInfo("Setup", "Process started");

    cb.display.setCursor(0, 0);
    cb.display.print("Nome Bluetooth: ");
    cb.display.setCursor(0, 1);
    cb.display.print(cb.getId());

    loggerInfo("Setup", "Process finished");
};

void CB5::execute()
{

    sys.serialPrint("Alarm status [0 (off) 1 (on)] : ");

    while (!sys.serialAvailable())
    {
    }
    string alarm = sys.serialRead();

    loggerWarn("CB5 Serial", " getting alarm status", "received alarm status: " + alarm);

    sys.serialPrintln("Dose status [N (no) or 1...9 (number of doses)] : ");
    while (!sys.serialAvailable())
    {
    }
    string dose = sys.serialRead();

    loggerWarn("CB5 Serial", "getting dose status", "received dose status: " + dose);

    sys.serialPrintln("Clear wheel bolts counter status [N (no) C (clear)] : ");
    while (!sys.serialAvailable())
    {
    }
    string wheelBoltsCounter = sys.serialRead();

    loggerWarn("CB5 Serial", "getting wheelBoltsCounter status", "received wheelBoltsCounter status: " + wheelBoltsCounter);

    string inf = "INF", extra = "xxxxxxx";
    string request = inf + alarm + dose + wheelBoltsCounter + extra;
    request += endPointBuilder(request);
    sys.serialPrintln("CS:  " + request[13]);
    sys.serialPrintln("13:  " + to_string((int)request[13]));
    sys.serialPrintln("14:  " + to_string((int)request[14]));
    sys.serialPrintln("12:  " + to_string((int)request[12]));

    ResponseModel responseModel = requestMiddleware.execute(request);
    sys.serialPrintln("RESPONSE: " + responseModel.tostring());
};
*/