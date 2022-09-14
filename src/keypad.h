/*
  Copyright Christian Mertens 2022
*/
#ifndef __KEYPAD_H__
#define __KEYPAD_H__

// Setup 5 way joystick
const uint8_t kUpPin = 22;
const uint8_t kDownPin = 23;
const uint8_t kLeftPin = 24;
const uint8_t kRightPin = 25;
const uint8_t kEntPin = 26;
class KeyPad 
{
  public:
    enum KeyVal{
      kUp = 0,
      kDown = 1,
      kLeft = 2,
      kRight = 3,
      kEnter = 4,
      kError = 254
    };

    KeyPad();
    void Setup();
    KeyVal Read();
    KeyVal GetLastReadedKey();

  private:
    KeyVal old_key_;

    KeyVal ReadValue();
};

#endif // __KEYPAD_H__