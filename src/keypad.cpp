/*
  Copyright Christian Mertens 2022
*/
#include <Arduino.h>
#include "keypad.h"

KeyPad::KeyPad() :
  old_key_(kError)
{
  
}

void KeyPad::Setup() {
  pinMode(kDownPin, INPUT_PULLUP);
  pinMode(kLeftPin, INPUT_PULLUP);
  pinMode(kRightPin, INPUT_PULLUP);
  pinMode(kEntPin, INPUT_PULLUP);
  pinMode(kUpPin, INPUT_PULLUP);
}

KeyPad::KeyVal KeyPad::Read() {
  KeyVal value = ReadValue();

  if (value != old_key_) {                 // if keypress is detected
    delay(250);                            // wait for debounce time
    value = ReadValue();
    if (value != old_key_) {
      old_key_ = value;
      return value;
    }
  }
  return old_key_;
}

KeyPad::KeyVal KeyPad::GetLastReadedKey()
{
  return old_key_;
}

KeyPad::KeyVal KeyPad::ReadValue() {
  KeyVal value = KeyPad::kError;

  if (digitalRead(kUpPin) == LOW) {
    value = KeyPad::kUp;
  } else if (digitalRead(kDownPin) == LOW) {
    value = KeyPad::kDown;
  } else if (digitalRead(kLeftPin) == LOW) {
    value = KeyPad::kLeft;
  } else if (digitalRead(kRightPin) == LOW) { 
    value = KeyPad::kRight;
  } else if (digitalRead(kEntPin) == LOW) { 
    value = KeyPad::kEnter;
  } 

  return value;
}