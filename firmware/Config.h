#pragma once

#include <stdint.h>

#define CONFIG_CURRENT_VERSION     2
#define CONFIG_FAN_ON_TEMP_C      25
#define CONFIG_FAN_ON_RPM        300
#define CONFIG_FAN_FULL_TEMP_C    50
#define CONFIG_FAN_FULL_RPM     1200
#define CONFIG_FAN_DELTA_TEMP_C    4
#define CONFIG_UNIT              'F'

struct Config {
  int16_t version;
  double fanOnTempC;
  double fanOnRPM;
  double fanFullTempC;
  double fanFullRPM;
  double fanDeltaTempC;
  char   unit;
  int32_t crc;

  // load checks version and crc, reset/save if fail
  bool load(uint16_t offset=0);

  // save sets version and crc
  bool save(uint16_t offset=0);

  // check version and crc
  bool valid() const;

  // default values (does not save)
  void reset();

  // does not update crc
  uint32_t computeCrc() const;
};
