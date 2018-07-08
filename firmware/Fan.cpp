#include <Arduino.h>
#include "dmath.h"
#include "Fan.h"

const int FAN_DUTY_PIN = -1;
const int FAN_ENABLE_PIN = 13;
double fan;

void FanSetup()
{
  if (FAN_DUTY_PIN >= 0) {
    pinMode(FAN_DUTY_PIN, OUTPUT);
  }
  if (FAN_ENABLE_PIN >= 0) {
    pinMode(FAN_ENABLE_PIN, OUTPUT);
  }
  fan = 0.0;
}

void FanUpdate()
{
  if (FAN_ENABLE_PIN >= 0) {
    digitalWrite(FAN_ENABLE_PIN, fan > 0.0);
  }
  if (FAN_DUTY_PIN >= 0) {
    analogWrite(FAN_DUTY_PIN,
                int(dround(dconstrainmap(fan,0.0,1.0,0.0,255.0))));
  }
}
