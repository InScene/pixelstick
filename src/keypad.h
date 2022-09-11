/*
  Copyright Christian Mertens 2022
*/
#ifndef __KEYPAD_H__
#define __KEYPAD_H__

// Setup 5 way joystick
#define UPPIN 22
#define DOWNPIN 23
#define LEFTPIN 24
#define RIGHTPIN 25
#define ENTPIN 26
class KeyPad 
{
  public:
    enum key_val{
      key_up = 0,
      key_down = 1,
      key_left = 2,
      key_right = 3,
      key_enter = 4,
      key_error = 254
    };

    KeyPad();
    void setup();
    key_val read();
    key_val getLastReadedKey();

  private:
    key_val oldkey;

    key_val read_value();
};

#endif // __KEYPAD_H__