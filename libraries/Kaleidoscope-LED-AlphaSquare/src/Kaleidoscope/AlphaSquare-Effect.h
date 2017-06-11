/* -*- mode: c++ -*-
 * Kaleidoscope-LED-AlphaSquare -- 4x4 pixel LED alphabet
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
#include <Kaleidoscope-LEDControl.h>

namespace kaleidoscope {
class AlphaSquareEffect : public LEDMode {
 public:
  AlphaSquareEffect(void);

  void begin(void) final;
  void update(void) final;

  static uint16_t length;
 private:
  static uint32_t end_time_left_, end_time_right_;
  static Key last_key_left_, last_key_right_;
  static uint8_t us_;

  static Key eventHandlerHook(Key key, uint8_t row, uint8_t col, uint8_t key_state);
};
}

extern kaleidoscope::AlphaSquareEffect AlphaSquareEffect;
