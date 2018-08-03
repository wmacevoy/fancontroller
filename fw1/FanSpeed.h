#pragma once

void FanControlInterrupt();

class FanSpeed : public Printable {
 friend void FanControlInterrupt();
 private: const uint8_t pin;
 private: bool found,found0,found1,found2;
 private: uint32_t last,last0,last1,last2;
 private: uint32_t interval;
 public: FanSpeed(uint8_t _pin);
 public: void setup();
 private: void isr();
 public: double current() const;
 public: size_t printTo(Print& p) const;
 public: bool valid() const;
};
