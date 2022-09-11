/*
  Copyright Christian Mertens 2022
*/
#ifndef __LOGIC_VALUES_H__
#define __LOGIC_VALUES_H__

#include <Arduino.h>

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
    void setBrightness(uint8_t value);
    void increaseBrightness();
    void decreaseBrightness();

    void storeValuesToEeprom();
    void restoreValuesFromEeprom();
    void resetValuesToDefault();

  private:
    unsigned long frameDelay;            // default for the frame delay
    unsigned long initDelay;             // Variable for delay between button press and start of light sequence
    uint16_t repeat;                     // Variable to select auto repeat (until select button is pressed again)
    unsigned long repeatDelay;           // Variable for delay between repeats
    uint16_t repeatTimes;                // Variable to keep track of number of repeats
    uint8_t brightness;                  // Variable and default for the Brightness of the strip

    uint16_t eepromReadUint16(uint8_t address);
    void eepromWriteUint16(uint8_t address, unsigned long value);
    unsigned long eepromReadULong(uint8_t address);
    void eepromWriteULong(uint8_t address, unsigned long value);
};

#endif // __LOGIC_VALUES_H__