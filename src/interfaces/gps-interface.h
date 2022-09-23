
#ifndef IGPS_H
#define IGPS_H
#include <string>
#include "types/error-or-string.h"
using namespace std;
class IGps
{
public:
    IGps(){};
    ErrorOrString getData();
    void setup();
};

#endif // IGPS_H