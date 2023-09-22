
#include <Arduino.h>
#include <iostream>
#include "delivery/cb5.h"
#include <Preferences.h>

using namespace std;

CB5 cb5;
Preferences preferences;
void setup()
{
  cb5.setup(&preferences);
}

void loop()
{
  cb5.execute();
}