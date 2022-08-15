#ifndef RESPONSE_BUILDER_H
#define RESPONSE_BUILDER_H

#include <Arduino.h>
#include "domain/model/cb.h"
#include "middleware/builder/check-sum-builder.h"

class ResponseBuilder
{
private:
    CheckSumBuilder checkSumBuilder;
public:
    ResponseBuilder();
    String buildSuccess(Cb cb);
};

#endif