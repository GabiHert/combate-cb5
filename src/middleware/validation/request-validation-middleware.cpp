#include "middleware/validation/request-validation-middleware.h"
#include "utils/utils.h"
#include "domain/builder/check-sum-builder.h"
#include "config/config.h"
#include "exceptions/error-type.h"

RequestValidationMiddleware::RequestValidationMiddleware(){};
pair<bool, ERROR_TYPE *> RequestValidationMiddleware::validate(string request)
{

    loggerInfo("RequestValidationMiddleware.validate", "Process started", "request: " + request);
    bool isProtocolValid = validateProtocol(request);
    bool isCheckSumValid = validateCheckSum(request);

    bool isRequestValid = isProtocolValid && isCheckSumValid;
    if (!isRequestValid)
    {
        loggerError("requestValidationMiddleware.validate", "Process error - first throw", "Invalid request");
        return make_pair(false, ERROR_TYPES().VALIDATION_ERROR);
    }
    return make_pair(isRequestValid, nullptr);
};
// todo: simpleV4 validation
//  bool RequestValidationMiddleware::validateSimpleV4(string request)
//  {
//      return request == "INF....."
//  };

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

    for (unsigned char requestCharacterIndex = 0; requestCharacterIndex <= requestLastIndex - 2; requestCharacterIndex++)
    {
        string protocolAllowedElementValues = CONFIG().PROTOCOL_ALLOWED_ELEMENTS_VALUES[requestCharacterIndex];
        unsigned char protocolAllowedElementValueLength = protocolAllowedElementValues.length() - 1;

        if (CONFIG_PROTOCOL_ANY_VALUE_VALID != protocolAllowedElementValues)
        {
            bool present = false;

            for (unsigned char allowedElementIndex = 0; allowedElementIndex <= protocolAllowedElementValueLength; allowedElementIndex++)
            {
                if (request[requestCharacterIndex] == protocolAllowedElementValues[allowedElementIndex])
                {
                    present = true;
                    break;
                };
            };

            if (!present)
            {
                loggerError("RequestValidationMiddleware.validateProtocol", "Process error", "request " + to_string(request[requestCharacterIndex]) + " character at index " + to_string(requestCharacterIndex) + " does not match the protocol allowed values;");
                return false;
            };
        };
    };

    return true;
};
