#include "middleware/validation/protocol-validation-middleware.h"
#include "utils/utils.h"
#include "config/config.h"

bool ProtocolValidationMiddleware::validate(String request)
{

    loggerInfo("RequestValidationMiddleware.validate", "Process started", " request: " + request);
    unsigned char requestLastIndex = request.length() - 1;

    unsigned char requestLength = request.length();
    if (requestLength != CONFIG().PROTOCOL_STRING_LENGTH)
    {

        loggerError("RequestValidationMiddleware.validate", "Process error", "error: request length is different from protocol; requestLength: " + String(requestLength));

        // TODO: throw error
    };

    if (request[requestLastIndex] != CONFIG().PROTOCOL_LF)
    {

        loggerError("RequestValidationMiddleware.validate", "Process error", "error: request Line feed is different from protocol; linefeed : " + request[requestLastIndex]);

        // TODO: throw error
    };

    if (request[requestLastIndex - 1] != CONFIG().PROTOCOL_CR)
    {

        loggerError("RequestValidationMiddleware.validate", "Process error", "error: request Line feed is different from protocol; carriageReturn : " + request[requestLastIndex - 1]);

        // TODO: throw error
    };

    String requestIdentifier = request.substring(CONFIG().PROTOCOL_IDENTIFIER_START_INDEX, CONFIG().PROTOCOL_IDENTIFIER_END_INDEX);

    for (int requestCharacterIndex = 0; requestCharacterIndex <= requestLastIndex - 2; requestCharacterIndex++)
    {
        String protocolAllowedElementValues = CONFIG().PROTOCOL_ALLOWED_ELEMENTS_VALUES[requestCharacterIndex];
        unsigned char protocolAllowedElementValueLength = protocolAllowedElementValues.length() - 1;

        if (CONFIG().PROTOCOL_ANY_VALUE_VALID != protocolAllowedElementValues)
        {
            bool present = false;

            for (int allowedElementIndex = 0; allowedElementIndex <= protocolAllowedElementValueLength; allowedElementIndex++)
            {
                if (request[requestCharacterIndex] == protocolAllowedElementValues[allowedElementIndex])
                {
                    present = true;
                    break;
                };
            };

            if (!present)
            {
                loggerWarn("RequestValidationMiddleware.validate", "Process warn", "request: " + request + "; charactereValue: " + request[requestCharacterIndex] + "; allowedValues: " + protocolAllowedElementValues);

                loggerError("RequestValidationMiddleware.validate", "Process error", "request " + String(request[requestCharacterIndex]) + " character at index " + String(requestCharacterIndex) + " does not match the protocol allowed values;");
            };
        };
    };

    loggerInfo("RequestValidationMiddleware.validate", "Process finished");
    return true;
};