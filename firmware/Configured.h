#pragma once

#include "Config.h"

struct Configured {
  Config &config;
  Configured(Config &_config);
  virtual void configure();
  virtual ~Configured();
};

