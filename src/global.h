/*
  Copyright Christian Mertens 2022
*/
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "display.h"
#include "keypad.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 lcd(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Display display = Display(lcd);

#endif // __GLOBAL_H__