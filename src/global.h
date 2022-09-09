/*
  Copyright Christian Mertens 2022
*/
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <StateMachine.h>
#include "display.h"
#include "keypad.h"

/************** Display Section *************/
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 lcd(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Display display = Display(lcd);

/************** Keypad Section *************/
KeyPad keypad = KeyPad();

/************** State Machine Section *************/
#define STATE_DEBUG 1

StateMachine machine = StateMachine();

#endif // __GLOBAL_H__