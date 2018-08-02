#pragma once

class FanPower : public Printable {
 private: const uint8_t pin;
 private: uint8_t level; // 0-255
 public: FanPower(uint8_t _pin);
 public: void setup();
 public: void set(uint8_t level);
 public: uint8_t get() const;
 public: size_t printTo(Print& p) const;
};
