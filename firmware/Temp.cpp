#include <Arduino.h>
#include <ArduinoUnit.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "Temp.h"

Temp::Temp(Config &_config, uint8_t _oneWireBus, uint8_t _resolution) 
: 
  config(_config),
  oneWire(_oneWireBus), 
  sensors(oneWire), 
  resolution(_resolution), 
  delayInMillis(750 / (1 << (12 - resolution))) 
{
  lastTemperature=0;
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
    if (state == 0) {
      sensors.begin();
      assertMore(sensors.getDSCount(),0);
      assertTrue(sensors.getAddress(address, 0));
      sensors.setResolution(address, resolution);
      sensors.setWaitForConversion(false);
      assertTrue(sensors.requestTemperaturesByAddress(tempDeviceAddress));
      state = 1;
    } else {
      state = 0;
      lastTemperature = sensors.getTempCByIndex(0);
      lastReading = millis();
      assertTrue(sensors.requestTemperaturesByAddress(tempDeviceAddress));
      state = 1;
    }
  }
}

size_t Temp:printTo(Print &p) {
  if (!valid()) {
    p.print("NONE ");
    p.print(config.units);
    return;
  }
  if (config.units == 'C') {
    p.print(lastTemperature);
    p.print("C");
  } else {
    double f = 1.8*lastTemperature*1.8+32;
    p.print(f);
    p.print("F");
  }
  

}

double Temp::current() const {
  if (valid()) {
    return lastTemperature;
  } else {
    return 100.0;
  }
}
