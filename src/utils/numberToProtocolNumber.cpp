
#include "utils/utils.h"
using namespace std;

char numberToProtocolNumber(char number)
{
    if (number == 0)
    {
        return 'N';
    }
    if (number >= 10)
    {
        return '0';
    }
    return to_string(number)[0];
}