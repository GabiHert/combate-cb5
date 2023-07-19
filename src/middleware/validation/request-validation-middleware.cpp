#include "middleware/validation/request-validation-middleware.h"
#include "utils/utils.h"
#include "domain/builder/check-sum-builder.h"
#include "config/config.h"
#include "exceptions/exceptions.h"

RequestValidationMiddleware::RequestValidationMiddleware(){};
ErrorOrBool RequestValidationMiddleware::validate(string request)
{

    loggerInfo("RequestValidationMiddleware.validate", "Process started", "request: " + request);
    bool isProtocolValid = validateProtocol(request);
    bool isCheckSumValid = validateCheckSum(request);

    bool isRequestValid = isProtocolValid && isCheckSumValid;
    if (!isRequestValid)
    {
        loggerError("requestValidationMiddleware.validate", "Process error - first throw", "Invalid request");
        return ErrorOrBool(EXCEPTIONS().VALIDATION_ERROR);
    }
    loggerInfo("RequestValidationMiddleware.validate", "Process finished", "isRequestValid: " + to_string(isRequestValid));
    return ErrorOrBool(isRequestValid);
};

bool RequestValidationMiddleware::validateCheckSum(string request)
{

    loggerInfo("RequestValidationMiddleware.validateCheckSum", "Process started", "request: " + request);

    string requestData = request.substr(CONFIG_PROTOCOL_DATA_START_INDEX, CONFIG_PROTOCOL_DATA_END_INDEX);

    int calculatedCS = checkSumBuilder.build(requestData);

    int receivedCS = (int)request[13];

    if (receivedCS != calculatedCS)
    {
        loggerError("RequestValidationMiddleware.validateCheckSum", "Process error", "Received CS (" + to_string(receivedCS) + ") is different from calculated CS (" + to_string(calculatedCS) + ")");
        return false;
    };

    loggerInfo("RequestValidationMiddleware.validateCheckSum", "Process finished", "request: " + request);
    return true;
};

bool RequestValidationMiddleware::validateProtocol(string request)
{

    loggerInfo("RequestValidationMiddleware.validateProtocol", "Process started", " request: " + request);
    unsigned char requestLastIndex = request.length() - 1;

    unsigned char requestLength = request.length();
    if (requestLength != CONFIG_PROTOCOL_STRING_LENGTH)
    {
        loggerError("RequestValidationMiddleware.validateProtocol", "Process error", "error: request length is different from protocol; requestLength: " + to_string(requestLength));
        return false;
    };

    if (request[requestLastIndex] != CONFIG_PROTOCOL_LF)
    {
        loggerError("RequestValidationMiddleware.validateProtocol", "Process error", "error: request Line feed is different from protocol; linefeed : " + request[requestLastIndex]);
        return false;
    };

    if (request[requestLastIndex - 1] != CONFIG_PROTOCOL_CR)
    {
        loggerError("RequestValidationMiddleware.validateProtocol", "Process error", "error: request Carriage Return is different from protocol; carriageReturn : " + request[requestLastIndex - 1]);
        return false;
    };

    string requestIdentifier = request.substr(CONFIG_PROTOCOL_IDENTIFIER_START_INDEX, CONFIG_PROTOCOL_IDENTIFIER_END_INDEX);
    if (requestIdentifier != "INF5" && requestIdentifier != "INF1" && requestIdentifier != "INF0")
    {
        loggerError("RequestValidationMiddleware.validateProtocol", "Process error", "invalid request identifier");
        return false;
    }

    char requestType = request[4];

    if (requestIdentifier == "INF5")
    {
        if (CONFIG().PROTOCOL_ALLOWED_REQUEST_TYPES.find(requestType) == CONFIG().PROTOCOL_ALLOWED_REQUEST_TYPES.npos)
        {
            loggerError("RequestValidationMiddleware.validateProtocol", "Process error", "invalid requestType");
            return false;
        }
    }

    auto allowedValues = CONFIG().PROTOCOL_ALLOWED_ELEMENTS_VALUES_R;

    switch (requestType)
    {
    case 'R':
        allowedValues = CONFIG().PROTOCOL_ALLOWED_ELEMENTS_VALUES_R;
        break;
    case 'D':
        allowedValues = CONFIG().PROTOCOL_ALLOWED_ELEMENTS_VALUES_D;
        break;
    case 'S':
        allowedValues = CONFIG().PROTOCOL_ALLOWED_ELEMENTS_VALUES_S;
        break;

    default:
        allowedValues = CONFIG().PROTOCOL_ALLOWED_ELEMENTS_VALUES_V4;
        break;
    }

    for (int requestCharacterIndex = 4; requestCharacterIndex <= requestLastIndex - 2; requestCharacterIndex++)
    {
        string protocolAllowedElementValues = allowedValues[requestCharacterIndex - 4];

        if (CONFIG_PROTOCOL_ANY_VALUE_VALID != protocolAllowedElementValues)
        {
            if (protocolAllowedElementValues.find(request[requestCharacterIndex]) == protocolAllowedElementValues.npos)
            {
                loggerWarn("RequestValidationMiddleware.validateProtocol", "Process warn", "request: " + request + "; charactereValue: " + request[requestCharacterIndex] + "; allowedValues: " + protocolAllowedElementValues);
                loggerError("RequestValidationMiddleware.validateProtocol", "Process error", "request " + to_string(request[requestCharacterIndex]) + " character at index " + to_string(requestCharacterIndex) + " does not match the protocol allowed values;");
                return false;
            };
        };
    };

    loggerInfo("RequestValidationMiddleware.validateProtocol", "Process finished");
    return true;
};
