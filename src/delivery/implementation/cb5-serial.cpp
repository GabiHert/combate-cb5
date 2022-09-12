#include "delivery/interfaces/cb5.h"
#include "utils/utils.h"
#include <Arduino.h>
#include "domain/cb/cb.h"
#include "middleware/request-middleware.h"
#include "config/config.h"
#include "interfaces/system-interface.h"
#include <string.h>
using namespace std;
#include "exceptions/validation-error.h"

Cb cb("CB5 DEV");
RequestMiddleware requestMiddleware(cb);
ISystem sys;

int buildCheckSum(string data)
{
    unsigned char dataLastIndex = data.length() - 1;
    int sum = 0;
    for (int i = 0; i <= dataLastIndex; i++)
    {
        sum += int(data[i]);
    };

    int CS = 256 - (sum % 256);

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
    char value = 0;

    value += HexDigit(*p++);

    if (*p != '\0')
    {
        value = value * 16 + HexDigit(*p);
    }
    return value;
}

string endPointBuilder(string request)
{
    string cs = to_string(buildCheckSum(request));
    string endPoint = "";

    for (unsigned i = 0; i < cs.length(); i += 2)
    {
        endPoint += HexByte(&cs[i]);
    };
    /*
         string cr = string(CONFIG().PROTOCOL_CR);
        for (unsigned i = 0; i < cr.length(); i += 2)
        {
            endPoint += HexByte(&cr[i]);
        };

        string lf = string(CONFIG().PROTOCOL_LF);
        for (unsigned i = 0; i < lf.length(); i += 2)
        {
            endPoint += HexByte(&lf[i]);
        };
    */
    endPoint += '\r';
    endPoint += '\n';
    sys.serialPrintln("END POINT: " + endPoint);
    return endPoint;
}

void CB5::setup()
{
    cb.setup();
    Serial.begin(CONFIG().SERIAL_BOUD_RATE); // TODO: usar classe System

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
    string request = alarm + dose + wheelBoltsCounter + extra;

    request += endPointBuilder(request);
    request = inf + request;

    ResponseModel responseModel = requestMiddleware.execute(request);
    sys.serialPrintln("RESPONSE: " + responseModel.tostring());
};