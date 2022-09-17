
#ifndef CHECKSUM_BUILDER_H
#define CHECKSUM_BUILDER_H
#include <string>
#include "interfaces/system-interface.h"
using namespace std;
class CheckSumBuilder
{

public:
    ISystem sys;
    CheckSumBuilder(){};
    int build(string request);
};
#endif // CHECKSUM_BUILDER_H
