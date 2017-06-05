/* -*- mode: c++ -*-
 * Kaleidoscope-IgnoranceIsBliss -- Ignore keys on a keyboard
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

#include <Kaleidoscope-IgnoranceIsBliss.h>

namespace kaleidoscope {

uint32_t IgnoranceIsBliss::left_hand_ignores;
uint32_t IgnoranceIsBliss::right_hand_ignores;

IgnoranceIsBliss::IgnoranceIsBliss(void) {
}

void IgnoranceIsBliss::begin(void) {
  event_handler_hook_use(this->eventHandlerHook);
}

Key IgnoranceIsBliss::eventHandlerHook(Key mapped_key, byte row, byte col, uint8_t key_state) {
  if (row >= ROWS || col >= COLS)
    return mapped_key;

  uint32_t current_hand = left_hand_ignores;

  if (col >= 8) {
    col = col - 8;
    current_hand = right_hand_ignores;
  }

  if (current_hand & SCANBIT(row, col))
    return Key_NoKey;

  return mapped_key;
}

}

kaleidoscope::IgnoranceIsBliss IgnoranceIsBliss;
