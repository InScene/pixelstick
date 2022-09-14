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

    unsigned long GetFrameDelay() const;
    void IncreaseFrameDelay();
    void DecreaseFrameDelay();
    unsigned long GetInitDelay() const;
    void IncreaseInitDelay1Sec();
    void DecreaseInitDelay1Sec();
    uint16_t GetRepeat() const;
    void IncreaseRepeat();
    void DecreaseRepeat();
    unsigned long GetRepeatDelay() const;
    void IncreaseRepeatDelay();
    void DecreaseRepeatDelay();
    uint16_t GetRepeatTimes() const;
    void IncreaseRepeatTimes();
    void DecreaseRepeatTimes();
    uint8_t GetBrightness() const;
    void SetBrightness(uint8_t value);
    void IncreaseBrightness();
    void DecreaseBrightness();

    void StoreValuesToEeprom();
    void RestoreValuesFromEeprom();
    void ResetValuesToDefault();

  private:
    const unsigned long kDefaultFrameDelay = 15;
    const unsigned long kDefaultInitDelay = 0;
    const uint16_t kDefaultRepeat = 0;
    const unsigned long kDefaultRepeatDelay = 0;
    const uint16_t kDefaultRepeatTimes = 1;
    const uint8_t kDefaultBrightness = 20;

    unsigned long frame_delay_;            // default for the frame delay
    unsigned long init_delay_;             // Variable for delay between button press and start of light sequence
    uint16_t repeat_;                     // Variable to select auto repeat (until select button is pressed again)
    unsigned long repeat_delay_;           // Variable for delay between repeats
    uint16_t repeat_times_;                // Variable to keep track of number of repeats
    uint8_t brightness_;                  // Variable and default for the Brightness of the strip

    uint16_t EepromReadUint16(uint8_t address);
    void EepromWriteUint16(uint8_t address, unsigned long value);
    unsigned long EepromReadULong(uint8_t address);
    void EepromWriteULong(uint8_t address, unsigned long value);
};

#endif // __LOGIC_VALUES_H__