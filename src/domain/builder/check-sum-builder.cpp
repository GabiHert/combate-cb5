#include "domain/builder/check-sum-builder.h"
#include "utils/utils.h"
#include "infra/system/system-interface.h"

char CheckSumBuilder::build(string data)
{
    unsigned char dataLastIndex = data.length();
    int sum = 0;
    for (unsigned char i = 0; i < dataLastIndex; i++)
    {
        sum += (int)data[i];
    };

    char CS = 256 - (sum % 256);
    if (CS > 127)
    {
        CS = 127 - (CS - 127);
    }

    return CS;
};