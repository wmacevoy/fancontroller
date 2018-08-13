#pragma once

#include <AStar32U4LCD.h>
#include "Config.h"

struct Display {
  Config &config;
  AStar32U4LCD &lcd;
  Display(Config &config, AStar32U4LCD &lcd);

  int state;
  void setup();
  void loop();
};
