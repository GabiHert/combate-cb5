
#ifndef GPRMC_PROTOCOL_VALIDATION_H
#define GPRMC_PROTOCOL_VALIDATION_H
#include <string>
using namespace std;

class GprmcProtocolValidation
{
public:
    GprmcProtocolValidation(){};
    bool validateStartHeader(string data);
    bool validateEndHeader(string data);
    bool validateStartHeader(char charactere, unsigned char position);
    bool validateEndHeader(char charactere, unsigned char position);
    bool validate(string data);
    bool isDataReliable(string data);
};

#endif
