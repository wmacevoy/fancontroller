#include <Arduino.h>
#include "dmath.h"
#include "Fan.h"

const int FAN_DUTY_PIN = 3;
const int FAN_ENABLE_PIN = 4;
double fan;

void FanSetup()
{
  pinMode(FAN_DUTY_PIN, OUTPUT);
  pinMode(FAN_ENABLE_PIN, OUTPUT);
  fan = 0.0;
}

void FanUpdate()
{
  digitalWrite(FAN_ENABLE_PIN, fan > 0.0);
  analogWrite(FAN_DUTY_PIN,
	      int(dround(dconstrainmap(fan,0.0,1.0,0.0,255.0))));
}
