/* -*- mode: c++ -*-
 * Kaleidoscope-GhostInTheFirmware -- Let the keyboard write for you!
 * Copyright (C) 2017  Gergely Nagy
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

namespace kaleidoscope {
class GhostInTheFirmware : public KaleidoscopePlugin {
 public:
  typedef struct {
    byte row;
    byte col;
    uint16_t pressTime;
    uint16_t delay;
  } GhostKey;
  static const GhostKey *ghost_keys;

  GhostInTheFirmware(void);

  void begin(void) final;
  static void activate(void);

 private:
  static bool is_active_;
  static bool is_pressed_;
  static uint16_t current_pos_;
  static uint32_t start_time_;
  static uint16_t press_timeout_;
  static uint16_t delay_timeout_;

  static void loopHook(bool is_post_clear);
};
}

extern kaleidoscope::GhostInTheFirmware GhostInTheFirmware;
