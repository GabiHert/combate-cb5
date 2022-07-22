#include <Arduino.h>

#ifndef CHECKSUM_BUILDER_H
#define CHECKSUM_BUILDER_H

class CheckSumBuilder
{
public:
    int build(String request);
};
#endif // CHECKSUM_BUILDER_H
