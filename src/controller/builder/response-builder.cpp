#include "controller/builder/response-builder.h"
#include "utils/utils.h"
#include "middleware/builder/check-sum-builder.h"

String ResponseBuilder::buildSuccess(Cb cb)
{
    loggerInfo("ResponseBuilder.build", "Process started");

    String response = "&";
    String errorCode = "000";
    String extraChar = "xxx";
    String whellBoltsCounterDecimal = String(cb.whellBoltsCounter[0]);
    String whellBoltsCounterUnit = String(cb.whellBoltsCounter[1]);
    String gpsData = cb.gps.data;

    response += whellBoltsCounterDecimal;
    response += whellBoltsCounterUnit;
    response += errorCode;
    response += extraChar;
    response += gpsData;

    int checkSum = checkSumBuilder.build(response);

    response += String(checkSum);

    loggerInfo("ResponseBuilder.build", "Process finished", "response: " + response);
    return response;
}

ResponseBuilder::ResponseBuilder() {}