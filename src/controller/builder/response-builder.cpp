#include "controller/builder/response-builder.h"
#include "utils/utils.h"
#include "middleware/builder/check-sum-builder.h"

String ResponseBuilder::buildSuccess(Cb cb)
{
    loggerInfo("ResponseBuilder.build", "Process started");

    String response = "&";
    String errorCode = "000";
    String extraChar = "xxx";
    String whellBoltsCounterDecimal = String(cb.getWhellBoltsCountDecimal());
    String whellBoltsCounterUnit = String(cb.getWhellBoltsCountUnit());
    String separator = ",";
    String gpsData = cb.gps.data;

    response += whellBoltsCounterDecimal;
    response += whellBoltsCounterUnit;
    response += errorCode;
    response += extraChar;
    response += separator;
    response += gpsData;

    int checkSum = checkSumBuilder.build(response);

    response += String(checkSum);

    //TODO: ResponseDto responseDto(response);
    //TODO: Fazer dessa classe um responseDto builder

    loggerInfo("ResponseBuilder.build", "Process finished", "response: " + response);
    return response;
}

ResponseBuilder::ResponseBuilder() {}