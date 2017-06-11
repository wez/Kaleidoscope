/* -*- mode: c++ -*-
 * Kaleidoscope-EEPROM-Keymap -- EEPROM-based keymap support.
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

#include <Kaleidoscope-EEPROM-Settings.h>
#include <Kaleidoscope-EEPROM-Keymap.h>
#include <Kaleidoscope-Focus.h>

namespace kaleidoscope {
uint16_t EEPROMKeymap::keymap_base_;
uint8_t EEPROMKeymap::max_layers_;

EEPROMKeymap::EEPROMKeymap(void) {
}

void EEPROMKeymap::begin(void) {
  USE_PLUGINS(&::EEPROMSettings);
}

void EEPROMKeymap::max_layers(uint8_t max) {
  max_layers_ = max;
  keymap_base_ = ::EEPROMSettings.requestSlice(max_layers_ * ROWS * COLS * 2);
}

Key EEPROMKeymap::getKey(uint8_t layer, byte row, byte col) {
  Key key;

  if (layer >= max_layers_)
    return Key_NoKey;

  uint16_t pos = ((layer * ROWS * COLS) + (row * COLS) + col) * 2;

  key.flags = EEPROM.read(keymap_base_ + pos);
  key.keyCode = EEPROM.read(keymap_base_ + pos + 1);

  return key;
}

Key EEPROMKeymap::getKeyOverride(uint8_t layer, byte row, byte col) {
  Key key;

  key = getKey(layer, row, col);
  if (key == Key_Transparent)
    key = Layer.getKeyFromPROGMEM(layer, row, col);
  return key;
}

uint16_t EEPROMKeymap::keymap_base(void) {
  return keymap_base_;
}

void EEPROMKeymap::updateKey(uint16_t base_pos, Key key) {
  EEPROM.update(keymap_base_ + base_pos * 2, key.flags);
  EEPROM.update(keymap_base_ + base_pos * 2 + 1, key.keyCode);
}

Key EEPROMKeymap::parseKey(void) {
  Key key;

  key.raw  = Serial.parseInt();

  return key;
}

void EEPROMKeymap::printKey(Key k) {
  ::Focus.printNumber(k.raw);
}

bool EEPROMKeymap::focusKeymap(const char *command) {
  if (strcmp_P(command, PSTR("keymap.map")) != 0)
    return false;

  if (Serial.peek() == '\n') {
    for (uint8_t layer = 0; layer < max_layers_; layer++) {
      for (uint8_t row = 0; row < ROWS; row++) {
        for (uint8_t col = 0; col < COLS; col++) {
          Key k = Layer.getKey(layer, row, col);

          printKey(k);
          ::Focus.printSpace();
        }
      }
    }
    Serial.println();
  } else {
    uint16_t i = 0;
    while ((Serial.peek() != '\n') && (i < ROWS * COLS * max_layers_)) {
      updateKey(i, parseKey());
      i++;
    }
  }

  return true;
}

bool EEPROMKeymap::focusKeymapTransfer(const char *command) {
  if (strcmp_P(command, PSTR("keymap.transfer")) != 0)
    return false;

  uint8_t layer = Serial.parseInt();

  for (uint8_t row = 0; row < ROWS; row++) {
    for (uint8_t col = 0; col < COLS; col++) {
      Key k = Layer.getKeyFromPROGMEM(layer, row, col);
      uint16_t pos = ((layer * ROWS * COLS) + (row * COLS) + col);

      updateKey(pos, k);
    }
  }

  return true;
}

}

kaleidoscope::EEPROMKeymap EEPROMKeymap;
