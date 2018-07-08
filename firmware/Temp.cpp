#include <Arduino.h>

#include "Temp.h"

const int TEMP_PIN = 4;

double temp;

static double GetTemp()
{
  // Leonardo atmega32u4 has 2.54v internal voltage reference
  analogReference(INTERNAL);
  return analogRead(TEMP_PIN)*(2.56/1023.0)*(1.0/0.010);
}

void TempSetup()
{
  temp = GetTemp();
}

void TempUpdate()
{
  temp = GetTemp();
}


