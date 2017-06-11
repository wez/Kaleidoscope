/* -*- mode: c++ -*-
 * Kaleidoscope-Heatmap -- Heatmap LED effect for Kaleidoscope.
 * Copyright (C) 2016, 2017  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <Kaleidoscope.h>
#include <Kaleidoscope-LEDControl.h>

namespace kaleidoscope {
class Heatmap : public LEDMode {
 public:
  Heatmap(void);

  static uint16_t update_delay;

  void begin(void) final;
  void update(void) final;
 private:
  static uint8_t heatmap_[ROWS][COLS];
  static uint16_t total_keys_;
  static uint8_t highest_count_;
  static uint32_t end_time_;

  static const float heat_colors_[][3];

  static void shiftStats(void);
  static cRGB computeColor(float v);

  static Key eventHook(Key mapped_key, byte row, byte col, uint8_t key_state);
  static void loopHook(bool is_post_clear);
};
}

extern kaleidoscope::Heatmap HeatmapEffect;
