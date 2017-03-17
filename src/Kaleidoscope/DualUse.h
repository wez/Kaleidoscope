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

#define MT(mod, key) (Key){ .raw = KaleidoscopePlugins::Ranges::DUM_FIRST + (((Key_ ## mod).keyCode - Key_LCtrl.keyCode) << 8) + (Key_ ## key).keyCode }
#define SFT_T(key) MT(LShift, key)
#define CTL_T(key) MT(LCtrl, key)
#define ALT_T(key) MT(LAlt, key)
#define GUI_T(key) MT(LGUI, key)

#define LT(layer, key) (Key){ .raw = KaleidoscopePlugins::Ranges::DUL_FIRST + (layer << 8) + (Key_ ## key).keyCode }

namespace KaleidoscopePlugins {
  class DualUse : public KaleidoscopePlugin {
  public:
    DualUse (void);

    virtual void begin (void) final;
    static void configure (uint8_t offAction);

    static uint16_t timeOut;

    void inject (Key key, uint8_t keyState);

  private:
    static uint16_t keyActionNeededMap;
    static uint16_t pressedMap;

    static uint32_t endTime;

    static Key specialAction (uint8_t specIndex);
    static void pressAllSpecials (byte row, byte col);

    static Key eventHandlerHook (Key mappedKey, byte row, byte col, uint8_t keyState);
  };
};

extern KaleidoscopePlugins::DualUse DualUse;
