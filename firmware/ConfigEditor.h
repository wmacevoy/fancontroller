#pragma once

struct ConfigEditor {
  Config &config;
  AStar32U4LCD &lcd;
  ConfigEditor(Config &config, AStar32U4LCD &lcd);

  int state;

  void setup();
  void loop();
};
