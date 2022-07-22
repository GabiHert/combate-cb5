#include "middleware/builder/check-sum-builder.h"
#include "utils/utils.h"

int CheckSumBuilder::build(String data)
{
    loggerInfo("CheckSumBuilder.build", "Process started");

    unsigned char dataLastIndex = data.length() - 1;
    int sum = 0;
    for (int i = 0; i <= dataLastIndex; i++)
    {
        sum += int(data[i]);
    };

    int CS = 256 - (sum % 256);

    loggerInfo("CheckSumBuilder.build", "Process finished", " requestData: " + data + "; CheckSum: " + String(CS));

    return CS;
};