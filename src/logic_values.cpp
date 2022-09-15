/*
  Copyright Christian Mertens 2022
*/
#include "logic_values.h"
#include <EEPROM.h>

const unsigned long kULongMax = 0xFFFFFFFF;
const unsigned long kOneSecInMs = 1000;
const unsigned long kOneHundredMs = 100;
const uint8_t kbrightnessMax = 100;
const uint16_t kRepeatMax = UINT16_MAX;
const unsigned long kRepeatDelayMax = kULongMax-kOneHundredMs;
const unsigned long kInitDelayMax = kULongMax-kOneSecInMs;
const unsigned long kFrameDelayMax = kULongMax;
const uint16_t kRepeatTimesMax = UINT16_MAX;

// EEPROM setup. saves all values in eeprom. the mega has 4kb of eeprom storage
// the current address in the EEPROM (i.e. which byte we're going to write to next)

// set addresses for save
const uint8_t kAddrFrameDelay = 0; // default for the frame delay
const uint8_t kAddrInitDelay = 10; // Variable for delay between button press and start of light sequence
const uint8_t kAddrRepeat = 20;    // Variable to select auto repeat (until select button is pressed again)
const uint8_t kAddrRepeatDelay = 30; // Variable for delay between repeats
const uint8_t kAddrRepeatTimes = 40;  // Variable to keep track of number of repeats
const uint8_t kAddrBrightness = 50;  // Variable and default for the Brightness of the strip


LogicValues::LogicValues() :
  frame_delay_(kDefaultFrameDelay),
  init_delay_(kDefaultInitDelay),
  repeat_(kDefaultRepeat),
  repeat_delay_(kDefaultRepeatDelay),
  repeat_times_(kDefaultRepeatTimes),
  brightness_(kDefaultBrightness)
{
  
}

unsigned long  LogicValues::GetFrameDelay() const
{
  return frame_delay_;
}

void LogicValues::IncreaseFrameDelay()
{
  if(frame_delay_ < kFrameDelayMax)
    frame_delay_++;
}

void LogicValues::DecreaseFrameDelay()
{
  if(frame_delay_ > 0)
    frame_delay_--;
}

unsigned long LogicValues::GetInitDelay() const
{
  return init_delay_;
}

void LogicValues::IncreaseInitDelay1Sec()
{
  if(init_delay_ <= kInitDelayMax)
    init_delay_ += kOneSecInMs;
}
  
void LogicValues::DecreaseInitDelay1Sec()
{
  if(init_delay_ >= kOneSecInMs)
    init_delay_ -= kOneSecInMs;
}

uint16_t LogicValues::GetRepeat() const
{
  return repeat_;
}

void LogicValues::IncreaseRepeat()
{
  if(repeat_ < kRepeatMax)
    repeat_++;
}

void LogicValues::DecreaseRepeat()
{
  if(repeat_ > 0)
    repeat_--;
}

unsigned long LogicValues::GetRepeatDelay() const
{
  return repeat_delay_;
}

void LogicValues::IncreaseRepeatDelay()
{
  if(repeat_delay_ <= kRepeatDelayMax)
    repeat_delay_ += kOneHundredMs;
}

void LogicValues::DecreaseRepeatDelay()
{
  if(repeat_delay_ >= kOneHundredMs)
    repeat_delay_ -= kOneHundredMs;
}

uint16_t LogicValues::GetRepeatTimes() const
{
  return repeat_times_;
}

void LogicValues::IncreaseRepeatTimes()
{
  if(repeat_times_ < kRepeatTimesMax)
    repeat_times_++;
}

void LogicValues::DecreaseRepeatTimes()
{
  if(repeat_times_ > 0)
    repeat_times_--;
}

uint8_t LogicValues::GetBrightness() const
{
  return brightness_;
}

void LogicValues::SetBrightness(uint8_t value)
{
  if(value <= kbrightnessMax)
    brightness_ = value;
}

void LogicValues::IncreaseBrightness()
{
  if(brightness_ <= kbrightnessMax)
    brightness_++;
}

void LogicValues::DecreaseBrightness()
{
  if(brightness_ > 0)
    brightness_--;
}

void LogicValues::StoreValuesToEeprom()
{
  unsigned long val_ulong;
  uint16_t val_uint16;
  uint8_t val;

  val_ulong = EepromReadULong(kAddrFrameDelay);
  if (val_ulong != frame_delay_) {
    EepromWriteULong(kAddrFrameDelay, frame_delay_);
  }

  val_ulong = EepromReadULong(kAddrInitDelay);
  if (val_ulong != init_delay_) {
    EepromWriteULong(kAddrInitDelay, init_delay_);
  }

  val_uint16 = EepromReadUint16(kAddrRepeat);
  if (val_uint16 != repeat_) {
    EepromWriteUint16(kAddrRepeat, repeat_);
  }

  val_ulong = EepromReadULong(kAddrRepeatDelay);
  if (val_ulong != repeat_delay_) {
    EepromWriteULong(kAddrRepeatDelay, repeat_delay_);
  }

  val_uint16 = EepromReadUint16(kAddrRepeatTimes);
  if (val_ulong != repeat_times_) {
    EepromWriteUint16(kAddrRepeatTimes, repeat_times_);
  }

  val = EEPROM.read(kAddrBrightness);
  if (val != brightness_) {
    EEPROM.write(kAddrBrightness, brightness_);
  }
}

void LogicValues::RestoreValuesFromEeprom()
{
  unsigned long val_ulong;
  uint16_t val_uint16;
  uint8_t val;

  val_ulong = EepromReadULong(kAddrFrameDelay);
  if (val_ulong >= 1 && val_ulong <= kFrameDelayMax) {
    frame_delay_ = val_ulong;
  }

  val_ulong = EepromReadULong(kAddrInitDelay);
  if (val_ulong >= 1 && val_ulong <= kInitDelayMax) {
    init_delay_ = val_ulong;
  }

  val_uint16 = EepromReadUint16(kAddrRepeat);
  if (val_uint16 >= 1 && val_uint16 <= kRepeatMax) {
    repeat_ = val_uint16;
  }

  val_ulong = EepromReadULong(kAddrRepeatDelay);
  if (val_ulong >= 1 && val_ulong <= kRepeatDelayMax) {
    repeat_delay_ = val_ulong;
  }

  val_uint16 = EepromReadUint16(kAddrRepeatTimes);
  if (val_ulong >= 1 && val_ulong <= kRepeatTimesMax) {
    repeat_times_ = val_ulong;
  }

  val = EEPROM.read(kAddrBrightness);
  if (val >= 1 && val <= kbrightnessMax) {
    brightness_ = val;
  }
 
}

void LogicValues::ResetValuesToDefault()
{
  frame_delay_ = kDefaultFrameDelay;
  init_delay_ = kDefaultInitDelay;
  repeat_ = kDefaultRepeat;
  repeat_delay_ = kDefaultRepeatDelay;
  repeat_times_ = kDefaultRepeatTimes;
  brightness_ = kDefaultBrightness;

  StoreValuesToEeprom();
}
  
uint16_t LogicValues::EepromReadUint16(uint8_t address) {
  uint16_t one = EEPROM.read(address);
  uint16_t two = EEPROM.read(address + 1);
  
  return ((one << 0) & 0xFF) + ((two << 8) & 0xFFFF);
}

void LogicValues::EepromWriteUint16(uint8_t address, unsigned long value) {
  byte two = (value & 0xFF);
  byte one = ((value >> 8) & 0xFF);
  
  EEPROM.write(address, one);
  EEPROM.write(address + 1, two);
}

unsigned long LogicValues::EepromReadULong(uint8_t address) {
  unsigned long one = EEPROM.read(address);
  unsigned long two = EEPROM.read(address + 1);
  unsigned long three = EEPROM.read(address + 2);
  unsigned long four = EEPROM.read(address + 3);
  
  return ((one << 0) & 0xFF) + ((two << 8) & 0xFFFF) + ((three << 16) & 0xFFFFFF) + ((four << 24) & 0xFFFFFFFF);
}

void LogicValues::EepromWriteULong(uint8_t address, unsigned long value) {
  byte one = (value & 0xFF);
  byte two = ((value >> 8) & 0xFF);
  byte three = ((value >> 16) & 0xFF);
  byte four = ((value >> 24) & 0xFF);
  
  EEPROM.write(address, one);
  EEPROM.write(address + 1, two);
  EEPROM.write(address + 2, three);
  EEPROM.write(address + 3, four);
}