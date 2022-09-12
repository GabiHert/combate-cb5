
#ifndef IGPS_H
#define IGPS_H
#include <string>
using namespace std;
class IGps
{
private:
    string location;

public:
    IGps(){};
    string getLocation();
    void setLocation();
    void setup();
};

#endif // IGPS_H