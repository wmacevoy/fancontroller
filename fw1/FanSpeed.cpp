#include <Arduino.h>
#include "FanSpeed.h"

static FanSpeed *me = 0;

void FanControlInterrupt() {
  me->rise();
}

FanSpeed::FanSpeed(uint8_t _pin) : pin(_pin) 
{ }

void FanSpeed::setup() {
  me = this;
  pinMode(pin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), FanControlInterrupt, RISING);
  state = 0;
}

void FanSpeed::enable() {
  state = 1;
  me = this;
}

void FanSpeed::disable() {
  state = 0;
}

void FanSpeed::rise() {
  switch(state) {
  case 0: return;
  case 1: last = micros(); state = 2; return;
  default: uint32_t now = micros(); interval = now - last; last=now; state = 3; return;
  }
}

double FanSpeed::current() const {
  // 2 pulses per revolution
  return state == 3 ? 500000.0/interval : 0;
}

size_t FanSpeed::printTo(Print& p) const {
  size_t sz = 0;
  sz += p.print(current());
  sz += p.print("Hz");
  if (!valid()) sz += p.print("?:");
  return sz;
}

bool FanSpeed::valid() const {
  return state == 3;
}

