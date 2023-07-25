#include "domain/builder/check-sum-builder.h"
#include "utils/utils.h"
#include "infra/system/system-interface.h"

int CheckSumBuilder::build(string data)
{
    loggerInfo("CheckSumBuilder.build", "Process started", "data: " + data);

    unsigned char dataLastIndex = data.length();
    int sum = 0;
    for (unsigned char i = 0; i < dataLastIndex; i++)
    {
        sum += (int)data[i];
    };

    int CS = 256 - (sum % 256);

    loggerInfo("CheckSumBuilder.build", "Process finished", " requestData: " + data + "; CheckSum: " + to_string(CS));

    return CS;
};