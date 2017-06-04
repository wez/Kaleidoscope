/* -*- mode: c++ -*-
 * AtmegaScanner -- Atmega-based keyboard scanner for Kaleidoscope
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

#include <Arduino.h>

template<uint8_t cols_, uint8_t rows_>
class AtmegaScanner {
 public:
  typedef struct {
    uint32_t all;
  } keydata_t;

  AtmegaScanner(void);

  bool readKeys(void);

  keydata_t leftHandState;
  keydata_t rightHandState;
  keydata_t previousLeftHandState;
  keydata_t previousRightHandState;

 private:
  void initCols(void);
  void unselectRows(void);
  void selectRow(uint8_t row);
  uint16_t readCols(void);
};

template<uint8_t cols_, uint8_t rows_>
void AtmegaScanner<cols_, rows_>::unselectRows(void) {
  DDRD &= ~0b00110000;
  PORTD &= ~0b00110000;

  DDRE &= ~0b01000100;
  PORTE &= ~0b01000100;
}

template<uint8_t cols_, uint8_t rows_>
void AtmegaScanner<cols_, rows_>::initCols(void) {
  DDRB &= ~(1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7);
  PORTB |= (1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7);
  DDRC &= ~(1<<7 | 1<<6);
  PORTC |= (1<<7 | 1<<6);
  DDRD &= ~(1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<7);
  PORTD |= (1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<7);
  DDRF &= ~(1<<6 | 1<<7);
  PORTF |= (1<<6 | 1<<7);
}

template<uint8_t cols_, uint8_t rows_>
void AtmegaScanner<cols_, rows_>::selectRow(uint8_t row) {
  switch (row) {
  case 0:
    DDRD  |= (1<<4);
    PORTD &= ~(1<<4);
    break;
  case 1:
    DDRD  |= (1<<5);
    PORTD &= ~(1<<5);
    break;
  case 2:
    DDRE  |= (1<<2);
    PORTE &= ~(1<<2);
    break;
  case 3:
    DDRE  |= (1<<6);
    PORTE &= ~(1<<6);
    break;
  default:
    break;
  }
}

template<uint8_t cols_, uint8_t rows_>
uint16_t AtmegaScanner<cols_, rows_>::readCols(void) {
  return (PINF&(1<<6) ? 0 : (1<<0)) |
         (PINF&(1<<7) ? 0 : (1<<1)) |
         (PINB&(1<<4) ? 0 : (1<<2)) |
         (PINB&(1<<5) ? 0 : (1<<3)) |
         (PINB&(1<<6) ? 0 : (1<<4)) |
         (PIND&(1<<7) ? 0 : (1<<5)) |
         (PINC&(1<<6) ? 0 : (1<<6)) |
         (PINC&(1<<7) ? 0 : (1<<7)) |
         (PIND&(1<<3) ? 0 : (1<<8)) |     // Rev.A and B
         (PIND&(1<<2) ? 0 : (1<<9)) |
         (PIND&(1<<1) ? 0 : (1<<10)) |
         (PIND&(1<<0) ? 0 : (1<<11)) |
         (PINB&(1<<7) ? 0 : (1<<12)) |
         (PINB&(1<<3) ? 0 : (1<<13));
}

/* ------------------------------------ */

template<uint8_t cols_, uint8_t rows_>
AtmegaScanner<cols_, rows_>::AtmegaScanner(void) {
  leftHandState.all = 0;
  rightHandState.all = 0;
  previousLeftHandState.all = 0;
  previousRightHandState.all = 0;

  unselectRows();
  initCols();
}

template<uint8_t cols_, uint8_t rows_>
bool AtmegaScanner<cols_, rows_>::readKeys() {
  previousLeftHandState = leftHandState;
  previousRightHandState = rightHandState;

  for (uint8_t i = 0; i < rows_; i++) {
    selectRow(i);
    uint16_t cols = readCols();

    for (uint8_t c = 0; c < cols_ / 2; c++) {
      uint8_t rowPos = i * (cols_ / 2);
      bitWrite(leftHandState.all, rowPos + c, bitRead(cols, c));
      bitWrite(rightHandState.all, rowPos + ((cols_ / 2 - 1) - c), bitRead(cols, (cols_ / 2) + c));
    }

    unselectRows();
  }

  return true;
}
