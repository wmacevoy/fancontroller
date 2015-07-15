#include <Arduino.h>
#include "dmath.h"
#include "Fan.h"

const int FAN_DUTY_PIN = 3;
const int FAN_ENABLE_PIN = 4;

void FanSetup()
{
  pinMode(FAN_DUTY_PIN, OUTPUT);
  pinMode(FAN_ENABLE_PIN, OUTPUT);
}

void FanUpdate(double duty)
{
  digitalWrite(FAN_ENABLE_PIN, duty > 0);
  analogWrite(FAN_DUTY_PIN,
	      int(dround(dconstrainmap(duty,0.0,1.0,0.0,255.0))));
}
