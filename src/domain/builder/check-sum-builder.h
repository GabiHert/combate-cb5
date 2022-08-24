
#ifndef CHECKSUM_BUILDER_H
#define CHECKSUM_BUILDER_H
#include <Arduino.h>

class CheckSumBuilder
{
public:
    int build(String request);
};
#endif // CHECKSUM_BUILDER_H
