#include "delivery/interfaces/cb5.h"
#include "utils/utils.h"
#include <Arduino.h>
#include "domain/cb/cb.h"
#include "middleware/request-middleware.h"
#include "config/config.h"
#include "interfaces/system-interface.h"

Cb cb("CB5 DEV");
RequestMiddleware requestMiddleware(cb);
ISystem sys;

int CheckSumBuilder(String data)
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

void CB5::setup()
{
    Serial.begin(CONFIG().SERIAL_BOUD_RATE);

    loggerInfo("Setup", "Process started");

    cb.setup();

    cb.display.setCursor(0, 0);
    cb.display.print("Nome Bluetooth: ");
    cb.display.setCursor(0, 1);
    cb.display.print(cb.getId());

    loggerInfo("Setup", "Process finished");
};

void CB5::execute()
{

    sys.serialPrint("Alarm status [0 (off) 1 (on)] : ");
    String alarm = sys.serialRead();
    sys.serialPrint("Dose status [N (no) or 0...9 (number of doses)] : ");
    String dose = sys.serialRead();
    sys.serialPrint("Clear wheel bolts counter status [N (no) C (clear)] : ");
    String wheelBoltsCounter = sys.serialRead();

    String inf = "INF", extra = "xxxxxxxx";
    String request = inf + alarm + dose + wheelBoltsCounter + extra;
    int cs = CheckSumBuilder(request);
    request += String(cs);

    requestMiddleware.execute(request);
};