#include <Arduino.h>
#include <ArduinoUnit.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "Temp.h"

Temp::Temp(Config &_config, uint8_t _oneWireBus, uint8_t _resolution) 
: 
  config(_config),
  oneWire(_oneWireBus), 
  sensors(&oneWire), 
  resolution(_resolution), 
  delayInMillis(750 / (1 << (12 - resolution))) 
{
  lastTemperatureRaw=DEVICE_DISCONNECTED_RAW;
  lastReading = -1000000000L; // yes int to unsigned
  timeout = 0;
  state = 0;
}

bool Temp::valid() const {
  const uint32_t maxAge = 1000;
  return uint32_t(millis() - lastReading)  <= maxAge;
}

void Temp::loop() {
  if (int32_t(millis() - timeout) > 0) {
    timeout = millis() + delayInMillis;
    Serial.print("temp state = ");
    Serial.print(state);
    Serial.println();
    if (state == 0) {
      sensors.begin();
      sensors.getAddress(address, 0);
      sensors.setResolution(address, resolution);
      sensors.setWaitForConversion(false);
      assertTrue(sensors.requestTemperaturesByAddress(address));
      state = 1;
    } else {
      state = 0;
      //      double value = sensors.getTempCByIndex(0);
      double value = sensors.getTemp(address);
      if (value == DEVICE_DISCONNECTED_RAW) return;
      lastTemperatureRaw = value;
      lastReading = millis();
      assertTrue(sensors.requestTemperaturesByAddress(address));
      state = 1;
    }
  }
}

size_t Temp::printTo(Print &p) const {
  p.print(current());
  p.print(config.unit);
  if (!valid()) {
    p.print("?");
  }
}

double Temp::current() const {
  if (valid()) {
    return config.unit == 'C' ? sensors.rawToCelsius(lastTemperatureRaw) : sensors.rawToFahrenheit(lastTemperatureRaw);
  } else {
    return config.unit == 'C' ? 100.0 : 212.0;
  }
}
