#include "utils/utils.h"
#include "middleware/validation/check-sum-validation-middleware.h"
#include "middleware/builder/check-sum-builder.h"
#include "config/config.h"
#include <Arduino.h>
CheckSumBuilder checkSumBuilder;
bool CheckSumValidationMiddleware::validate(String request)
{
    loggerInfo("CheckSumValidation.validate", "Process started", "request: " + String(request));

    String requestData = request.substring(CONFIG().PROTOCOL_DATA_START_INDEX, CONFIG().PROTOCOL_DATA_END_INDEX);

    int calculatedCS = checkSumBuilder.build(requestData);

    int receivedCS = int(request[13]);

    if (receivedCS != calculatedCS)
    {
        loggerError("CheckSumValidation.validate", "Process error", "Received CS (" + String(receivedCS) + ") is different from calculated CS (" + String(calculatedCS) + ")");
        // TODO: Throw error
    };

    loggerInfo("CheckSumValidation.validate", "Process finished", "request: " + String(request));
    return true;
}