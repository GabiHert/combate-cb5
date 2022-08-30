
#include <Arduino.h>
#include <iostream>
#include "delivery/interfaces/cb5.h"
using namespace std;


CB5 cb5;

void setup()
{
  cb5.setup();
}

void loop()
{
  cb5.execute();
}