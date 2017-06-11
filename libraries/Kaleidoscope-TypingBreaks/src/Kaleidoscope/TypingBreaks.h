/* -*- mode: c++ -*-
 * Kaleidoscope-TypingBreaks -- Enforced typing breaks
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

class TypingBreaks : public KaleidoscopePlugin {
 public:
  TypingBreaks(void);

  void begin(void) final;

  static void enableEEPROM(void);
  static bool focusHook(const char *command);

  typedef struct settings_t {
    uint32_t idle_time_limit;
    uint32_t lock_time_out;
    uint32_t lock_length;
    uint16_t left_hand_max_keys;
    uint16_t right_hand_max_keys;
  } settings_t;

  static settings_t settings;

 private:
  static uint32_t session_start_time_;
  static uint32_t lock_start_time_;
  static uint32_t last_key_time_;
  static uint16_t left_hand_keys_;
  static uint16_t right_hand_keys_;

  static uint16_t settings_base_;

  static Key eventHandlerHook(Key mapped_key, byte row, byte col, uint8_t key_state);
};

}

extern kaleidoscope::TypingBreaks TypingBreaks;

void TypingBreak(bool is_locked);

#define FOCUS_HOOK_TYPINGBREAKS FOCUS_HOOK(TypingBreaks.focusHook,        \
                                           "typingbreaks.idleTimeLimit\n" \
                                           "typingbreaks.lockTimeOut\n"   \
                                           "typingbreaks.lockLength\n"    \
                                           "typingbreaks.leftMaxKeys\n"   \
                                           "typingbreaks.rightMaxKeys")
