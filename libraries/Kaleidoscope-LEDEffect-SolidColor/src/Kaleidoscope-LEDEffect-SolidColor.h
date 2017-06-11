#pragma once

#include "Kaleidoscope-LEDControl.h"

class LEDSolidColor : public LEDMode {
 public:
  LEDSolidColor(uint8_t r, uint8_t g, uint8_t b);

  void init(void) final;

 private:
  uint8_t r, g, b;
};
