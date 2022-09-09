/*
  Copyright Christian Mertens 2022
*/
#ifndef __LOGIC_VALUES_H__
#define __LOGIC_VALUES_H__

#include <Arduino.h>

#define STRIP_LENGTH 144                  // Set the number of LEDs the LED Strip

class LogicValues 
{
  public:
    LogicValues();

    unsigned long getFrameDelay() const;
    void increaseFrameDelay();
    void decreaseFrameDelay();
    unsigned long getInitDelay() const;
    void increaseInitDelay1Sec();
    void decreaseInitDelay1Sec();
    uint16_t getRepeat() const;
    void increaseRepeat();
    void decreaseRepeat();
    unsigned long getRepeatDelay() const;
    void increaseRepeatDelay();
    void decreaseRepeatDelay();
    uint16_t getRepeatTimes() const;
    void increaseRepeatTimes();
    void decreaseRepeatTimes();
    uint8_t getBrightness() const;
    void increaseBrightness();
    void decreaseBrightness();

  private:
    unsigned long frameDelay;            // default for the frame delay
    unsigned long initDelay;             // Variable for delay between button press and start of light sequence
    uint16_t repeat;                     // Variable to select auto repeat (until select button is pressed again)
    unsigned long repeatDelay;           // Variable for delay between repeats
    uint16_t repeatTimes;                // Variable to keep track of number of repeats
    uint8_t brightness;                  // Variable and default for the Brightness of the strip
};

#endif // __LOGIC_VALUES_H__