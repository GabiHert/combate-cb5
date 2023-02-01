
#ifndef CHECKSUM_BUILDER_H
#define CHECKSUM_BUILDER_H
#include <string>
#include "infra/system/system-interface.h"
using namespace std;
class CheckSumBuilder
{

public:
    CheckSumBuilder(){};
    int build(string request);
};
#endif // CHECKSUM_BUILDER_H
