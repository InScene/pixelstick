/*
  Copyright Christian Mertens 2022
*/
#include <Arduino.h>
#include "keypad.h"

KeyPad::KeyPad() :
  oldkey(key_error)
{
  
}

void KeyPad::setup() {
  pinMode(DOWNPIN, INPUT_PULLUP);
  pinMode(LEFTPIN, INPUT_PULLUP);
  pinMode(RIGHTPIN, INPUT_PULLUP);
  pinMode(ENTPIN, INPUT_PULLUP);
  pinMode(UPPIN, INPUT_PULLUP);
}

KeyPad::key_val KeyPad::read() {
  key_val value = read_value();

  if (value != oldkey) {                    // if keypress is detected
    delay(250);                            // wait for debounce time
    value = read_value();
    if (value != oldkey) {
      oldkey = value;
      return value;
    }
  }
  return oldkey;
}

KeyPad::key_val KeyPad::getLastReadedKey()
{
  return oldkey;
}

KeyPad::key_val KeyPad::read_value() {
  key_val value = KeyPad::key_error;

  if (digitalRead(UPPIN) == LOW) {
    value = KeyPad::key_up;
  } else if (digitalRead(DOWNPIN) == LOW) {
    value = KeyPad::key_down;
  } else if (digitalRead(LEFTPIN) == LOW) {
    value = KeyPad::key_left;
  } else if (digitalRead(RIGHTPIN) == LOW) { 
    value = KeyPad::key_right;
  } else if (digitalRead(ENTPIN) == LOW) { 
    value = KeyPad::key_enter;
  } 

  return value;
}