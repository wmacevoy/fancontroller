#include <Arduino.h>
#include "dmath.h"
#include "UpdateFan.h"

const int FAN_PIN = 3;

void UpdateFan(double duty)
{
  pinMode(FAN_PIN, OUTPUT);  
  analogWrite(FAN_PIN,int(dround(dconstrainmap(duty,0.0,1.0,0.0,255.0))));
}
