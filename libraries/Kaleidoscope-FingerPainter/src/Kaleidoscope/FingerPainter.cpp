/* -*- mode: c++ -*-
 * Kaleidoscope-FingerPainter -- On-the-fly keyboard painting.
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

#include <Kaleidoscope-FingerPainter.h>

#include <Kaleidoscope-EEPROM-Settings.h>
#include <Kaleidoscope-Focus.h>
#include <Kaleidoscope-LEDControl.h>
#include <Kaleidoscope-LED-Palette-Theme.h>

namespace kaleidoscope {

uint16_t FingerPainter::color_base_;
bool FingerPainter::edit_mode_;

FingerPainter::FingerPainter(void) {
}

void FingerPainter::begin(void) {
  USE_PLUGINS(&::LEDPaletteTheme);

  LEDMode::begin();
  event_handler_hook_use(eventHandlerHook);

  color_base_ = ::LEDPaletteTheme.reserveThemes(1);
}

void FingerPainter::update(void) {
  ::LEDPaletteTheme.updateHandler(color_base_, 0);
}

void FingerPainter::toggle(void) {
  edit_mode_ = !edit_mode_;
}

Key FingerPainter::eventHandlerHook(Key mapped_key, byte row, byte col, uint8_t key_state) {
  if (!edit_mode_)
    return mapped_key;

  if (!key_toggled_on(key_state))
    return Key_NoKey;

  if (row >= ROWS || col >= COLS)
    return Key_NoKey;

  uint8_t color_index = ::LEDPaletteTheme.lookupColorIndexAtPosition(color_base_, KeyboardHardware.get_led_index(row, col));

  // Find the next color in the palette that is different.
  // But do not loop forever!
  bool turn_around = false;
  cRGB old_color = ::LEDPaletteTheme.lookupPaletteColor(color_index), new_color = old_color;
  while (memcmp(&old_color, &new_color, sizeof(cRGB)) == 0) {
    color_index++;
    if (color_index > 15) {
      color_index = 0;
      if (turn_around)
        break;
      turn_around = true;
    }
    new_color = ::LEDPaletteTheme.lookupPaletteColor(color_index);
  }

  ::LEDPaletteTheme.updateColorIndexAtPosition(color_base_, KeyboardHardware.get_led_index(row, col), color_index);

  return Key_NoKey;
}

bool FingerPainter::focusHook(const char *command) {
  enum {
    TOGGLE,
    CLEAR,
  } sub_command;

  if (strncmp_P(command, PSTR("fingerpainter."), 14) != 0)
    return false;

  if (strcmp_P(command + 14, PSTR("toggle")) == 0)
    sub_command = TOGGLE;
  else if (strcmp_P(command + 14, PSTR("clear")) == 0)
    sub_command = CLEAR;
  else
    return false;

  if (sub_command == CLEAR) {
    for (uint16_t i = 0; i < ROWS * COLS / 2; i++) {
      EEPROM.update(color_base_ + i, 0);
    }
    return true;
  }

  ::FingerPainter.activate();
  toggle();

  return true;
}

}

kaleidoscope::FingerPainter FingerPainter;
