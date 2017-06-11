/* -*- mode: c++ -*-
 * Kaleidoscope-DualUse -- Dual use keys for Kaleidoscope
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
#include <Kaleidoscope-Ranges.h>

#define MT(mod, key) (Key) { .raw = kaleidoscope::ranges::DUM_FIRST + (((Key_ ## mod).keyCode - Key_LeftControl.keyCode) << 8) + (Key_ ## key).keyCode }
#define SFT_T(key) MT(LeftShift, key)
#define CTL_T(key) MT(LeftControl, key)
#define ALT_T(key) MT(LeftAlt, key)
#define GUI_T(key) MT(LeftGui, key)

#define LT(layer, key) (Key) { .raw = kaleidoscope::ranges::DUL_FIRST + (layer << 8) + (Key_ ## key).keyCode }

namespace kaleidoscope {
class DualUse : public KaleidoscopePlugin {
 public:
  static uint16_t time_out;

  DualUse(void);

  void begin(void) final;

  void inject(Key key, uint8_t key_state);

 private:
  static uint16_t key_action_needed_map_;
  static uint16_t pressed_map_;

  static uint32_t end_time_;

  static Key specialAction(uint8_t spec_index);
  static void pressAllSpecials(byte row, byte col);

  static Key eventHandlerHook(Key mapped_key, byte row, byte col, uint8_t key_state);
};
}

extern kaleidoscope::DualUse DualUse;
