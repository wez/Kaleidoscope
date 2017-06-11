#pragma once

#define IS_MACRO       B00100000

#define M(n)           (Key){ n, KEY_FLAGS|SYNTHETIC|IS_MACRO }
#define Key_macroKey1  M(1)
#define Key_macroKey2  M(2)
#define Key_macroKey3  M(3)
#define Key_macroKey4  M(4)
#define Key_macroKey5  M(5)
#define Key_macroKey6  M(6)
#define Key_macroKey7  M(7)
#define Key_macroKey8  M(8)
#define Key_macroKey9  M(9)
#define Key_macroKey10 M(10)
