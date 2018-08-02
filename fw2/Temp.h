#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>
#include "Config.h"

class Temp : public Printable {
 private: Config &config;
 private: OneWire oneWire;
 private: DallasTemperature sensors;
 private: const uint8_t resolution;
 private: const uint16_t delayInMillis;
 private: DeviceAddress address;
 private: uint32_t lastReading;
 private: uint32_t timeout;
 private: uint8_t state;
 private: int16_t lastTemperatureRaw;
 public: Temp(Config &_config, uint8_t _oneWireBus, uint8_t _resolution = 12);
 public: double current() const;
 public: size_t printTo(Print& p) const;
 public: bool valid() const;
 public: void loop();
};
