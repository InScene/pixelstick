/*
  Copyright Christian Mertens 2022
*/
#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include <Arduino.h>

// Setup 5 way joystick
int uppin = 22;
int downpin = 23;
int leftpin = 24;
int rightpin = 25;
int entpin = 26;

int key = -1;
int oldkey = -1;

void keypad_setup() {
  pinMode(downpin, INPUT_PULLUP);
  pinMode(leftpin, INPUT_PULLUP);
  pinMode(rightpin, INPUT_PULLUP);
  pinMode(entpin, INPUT_PULLUP);
  pinMode(uppin, INPUT_PULLUP);
}

int keypad_read() {
  {
    if (digitalRead(uppin) == LOW) key = 1;
    else key = -1;
  }
  {
    if (digitalRead(downpin) == LOW) key = 2;
    else key = -1;
  }
  {
    if (digitalRead(leftpin) == LOW) key = 3;
    //else key = oldkey;
  }
  {
    if (digitalRead(rightpin) == LOW) key = 0;
    //else key = oldkey;
  }
  {
    if (digitalRead(entpin) == LOW) key = 4;
    //else key = oldkey;
  }

  if (key != oldkey) {                    // if keypress is detected
    delay(250);                            // wait for debounce time
    key = key;
    if (key != oldkey) {
      oldkey = key;
      if (key >= 0) {
        return key;
      }
    }
  }
  return key;
};

#endif // __KEYPAD_H__