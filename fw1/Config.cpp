#include <Arduino.h>
#include "Config.h"

// https://github.com/bakercp/CRC32
#include <CRC32.h>

// https://github.com/mmurdoch/arduinounit
#include <ArduinoUnit.h>

#include <EEPROM.h>

bool Config::load(uint16_t offset) {
  for (int i=0; i<sizeof(Config); ++i) {
    ((uint8_t*)(this))[i]=EEPROM.read(i);
  }
  if (!valid()) {
    Test::out->println(F("config invalid - reset."));
    reset();
    save();
    return false;
  }
  return true;
}

bool Config::save(uint16_t offset) {
  bool ok = true;
  version = CONFIG_CURRENT_VERSION;
  crc=computeCrc();
  for (int i=0; i<sizeof(Config); ++i) {
    uint8_t newData = ((const uint8_t*)(this))[i];
    uint8_t oldData = ((uint8_t*)(this))[i]=EEPROM.read(i);
    if (newData != oldData) {
      EEPROM.write(i,newData);
      ok = ok && (EEPROM.read(i) == newData);
    }
  }
  assertTrue(ok,F("save error"));
  return ok;
}

bool Config::valid() const {
  return version == CONFIG_CURRENT_VERSION && crc == computeCrc();
}

uint32_t Config::computeCrc() const {
  CRC32 crc32;
  for (int i=0; i<sizeof(Config)-4; ++i) {
    crc32.update(((uint8_t*)(this))[i]);
  }
  return crc32.finalize();
}

void Config::reset() {
  version = CONFIG_CURRENT_VERSION;
  fanOnTempC = CONFIG_FAN_ON_TEMP_C;
  fanOnRPM = CONFIG_FAN_ON_RPM;
  fanFullTempC = CONFIG_FAN_FULL_TEMP_C;
  fanFullRPM = CONFIG_FAN_FULL_RPM;
  fanDeltaTempC = CONFIG_FAN_DELTA_TEMP_C;
  unit = CONFIG_UNIT;
  crc = computeCrc();
}

const uint16_t TEST_OFFSET=sizeof(Config);

test(config_reset) {
  Config cfg;
  cfg.reset();
  assertEqual(cfg.version, CONFIG_CURRENT_VERSION);
  assertEqual(cfg.fanOnTempC, CONFIG_FAN_ON_TEMP_C);
  assertEqual(cfg.fanOnRPM, CONFIG_FAN_ON_RPM);
  assertEqual(cfg.fanFullTempC, CONFIG_FAN_FULL_TEMP_C);
  assertEqual(cfg.fanFullRPM, CONFIG_FAN_FULL_RPM);
  assertEqual(cfg.fanDeltaTempC, CONFIG_FAN_DELTA_TEMP_C);
  assertEqual(cfg.unit, CONFIG_UNIT);
}

test(config_load) {
  Config cfg;
  cfg.reset();
  double onTempC = 50;
  double fullTempC = 100;
  cfg.fanOnTempC = onTempC;
  cfg.fanFullTempC = fullTempC;
  assertTrue(cfg.save(TEST_OFFSET));
  cfg.reset();
  assertTrue(cfg.load(TEST_OFFSET));
  assertEqual(cfg.fanOnTempC, onTempC);
  assertEqual(cfg.fanFullTempC, fullTempC);
}
