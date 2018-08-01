#pragma once

void FanControlInterrupt();

class FanSpeed : public Printable {
 friend void FanControlInterrupt();
 private: uint8_t state;
 private: const uint8_t pin;
 private: uint32_t last;
 private: uint32_t interval;
 public: FanSpeed(uint8_t _pin);
 public: void setup();
 public: void enable();
 public: void disable();
 private: void rise();
 public: double current() const;
 public: size_t printTo(Print& p) const;
 public: bool valid() const;
};
