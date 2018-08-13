#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>

class Temp : Printable {
 private: Config &config;
 private: OneWire oneWire;
 private: DallasTemperature sensors;
 private: const uint8_t resolution;
 private: const uint16_t delayInMillis;
 private: DeviceAddress address;
 private: uint32_t lastReading;
 private: double lastTemperature;
 public: Temp(Config &_config, uint8_t _oneWireBus, int _resolution = 12);
 public: double current() const;
 public: size_t printTo(Print& p) const;
 public: bool valid() const;
 public: void loop();
};
