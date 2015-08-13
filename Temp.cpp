#include <Arduino.h>

#include "Temp.h"

const int TEMP_PIN = 0;

double temp;

static double GetTemp()
{
  analogReference(INTERNAL);
  return analogRead(TEMP_PIN)*1023.0/1.1*0.01;
}

void TempSetup()
{
  temp = GetTemp();
}

void TempUpdate()
{
  temp = GetTemp();
}


