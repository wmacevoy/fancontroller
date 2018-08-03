#include <Arduino.h>
#include "FanSpeed.h"

static FanSpeed *me = 0;

void FanControlInterrupt() {
  me->isr();
}

FanSpeed::FanSpeed(uint8_t _pin) : pin(_pin) 
{ }

void FanSpeed::setup() {
  me = this;
  pinMode(pin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), FanControlInterrupt, CHANGE);
  last=last0=last1=last2=0;
  found=found0=found1=found2=false;
}

void FanSpeed::isr() {
  bool on = digitalRead(pin);

  if (on) {
    last = micros();
    found = true;
    return;
  } else if (found) {
    uint32_t now = micros(); 
    if (int32_t(micros() - last) > 10000L) {
      found2 = found1;
      last2 = last1;
      found1 = found0;
      last1 = last0;
      found0 = true;
      last0 = last;
    }
  }
}

double FanSpeed::current() const {
  if (found2) {
    uint32_t delta = last0 - last2;
    if (delta > 10000L && delta < 1000000L) {
      return 1000000.0 / delta;
    }
  }
  return 0;
}

size_t FanSpeed::printTo(Print& p) const {
  size_t sz = 0;
  sz += p.print(current());
  sz += p.print("Hz");
  if (!valid()) sz += p.print("?:");
  return sz;
}

bool FanSpeed::valid() const {
  return found2;
}

