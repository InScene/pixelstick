/*
  Copyright Christian Mertens 2022
*/
#include "logic_values.h"
#include <EEPROM.h>

#define DEFAULT_FRAME_DELAY 15
#define DEFAULT_INIT_DELAY 0
#define DEFAULT_REPEAT 0
#define DEFAULT_REPEAT_DELAY 0
#define DEFAULT_REPEAT_TIMES 1
#define DEFAULT_BRIGHTNESS 20

#define ULONG_MAX 0xFFFFFFFF
#define OneSecInMs 1000
#define OneHundredMs 100
#define BRIGHTNESS_MAX 100
#define REPEAT_MAX UINT16_MAX
#define REPEAT_DELAY_MAX (ULONG_MAX-OneHundredMs)
#define INIT_DELAY_MAX (ULONG_MAX-OneSecInMs)
#define FRAME_DELAY_MAX ULONG_MAX
#define REPEAT_TIMES_MAX UINT16_MAX

// EEPROM setup. saves all values in eeprom. the mega has 4kb of eeprom storage
// the current address in the EEPROM (i.e. which byte we're going to write to next)

// set addresses for save
#define addrframeDelay 0                        // default for the frame delay
#define addrinitDelay 10                        // Variable for delay between button press and start of light sequence
#define addrrepeat 20                           // Variable to select auto repeat (until select button is pressed again)
#define addrrepeatDelay 30                     // Variable for delay between repeats
#define addrrepeatTimes 40                      // Variable to keep track of number of repeats
#define addrbrightness 50                       // Variable and default for the Brightness of the strip


LogicValues::LogicValues() :
  frameDelay(DEFAULT_FRAME_DELAY),
  initDelay(DEFAULT_INIT_DELAY),
  repeat(DEFAULT_REPEAT),
  repeatDelay(DEFAULT_REPEAT_DELAY),
  repeatTimes(DEFAULT_REPEAT_TIMES),
  brightness(DEFAULT_BRIGHTNESS)
{
  
}

unsigned long  LogicValues::getFrameDelay() const
{
  return frameDelay;
}

void LogicValues::increaseFrameDelay()
{
  if(frameDelay < FRAME_DELAY_MAX)
    frameDelay++;
}

void LogicValues::decreaseFrameDelay()
{
  if(frameDelay > 0)
    frameDelay--;
}

unsigned long LogicValues::getInitDelay() const
{
  return initDelay;
}

void LogicValues::increaseInitDelay1Sec()
{
  if(initDelay <= INIT_DELAY_MAX)
    initDelay += OneSecInMs;
}
  
void LogicValues::decreaseInitDelay1Sec()
{
  if(initDelay >= OneSecInMs)
    initDelay -= OneSecInMs;
}

uint16_t LogicValues::getRepeat() const
{
  return repeat;
}

void LogicValues::increaseRepeat()
{
  if(repeat < REPEAT_MAX)
    repeat++;
}

void LogicValues::decreaseRepeat()
{
  if(repeat > 0)
    repeat--;
}

unsigned long LogicValues::getRepeatDelay() const
{
  return repeatDelay;
}

void LogicValues::increaseRepeatDelay()
{
  if(repeatDelay <= REPEAT_DELAY_MAX)
    repeatDelay += OneHundredMs;
}

void LogicValues::decreaseRepeatDelay()
{
  if(initDelay >= OneHundredMs)
    initDelay -= OneHundredMs;
}

uint16_t LogicValues::getRepeatTimes() const
{
  return repeatTimes;
}

void LogicValues::increaseRepeatTimes()
{
  if(repeatTimes < REPEAT_TIMES_MAX)
    repeatTimes++;
}

void LogicValues::decreaseRepeatTimes()
{
  if(repeatTimes > 0)
    repeatTimes--;
}

uint8_t LogicValues::getBrightness() const
{
  return brightness;
}

void LogicValues::setBrightness(uint8_t value)
{
  if(value <= BRIGHTNESS_MAX)
    brightness = value;
}

void LogicValues::increaseBrightness()
{
  if(brightness <= BRIGHTNESS_MAX)
    brightness++;
}

void LogicValues::decreaseBrightness()
{
  if(brightness > 0)
    brightness--;
}

void LogicValues::storeValuesToEeprom()
{
  unsigned long valULong;
  uint16_t valUint16;
  uint8_t val;

  valULong = eepromReadULong(addrframeDelay);
  if (valULong != frameDelay) {
    eepromWriteULong(addrframeDelay, frameDelay);
  }

  valULong = eepromReadULong(addrinitDelay);
  if (valULong != initDelay) {
    eepromWriteULong(addrinitDelay, initDelay);
  }

  valUint16 = eepromReadUint16(addrrepeat);
  if (valUint16 != repeat) {
    eepromWriteUint16(addrrepeat, repeat);
  }

  valULong = eepromReadULong(addrrepeatDelay);
  if (valULong != repeatDelay) {
    eepromWriteULong(addrrepeatDelay, repeatDelay);
  }

  valUint16 = eepromReadUint16(addrrepeatTimes);
  if (valULong != repeatTimes) {
    eepromWriteUint16(addrrepeatTimes, repeatTimes);
  }

  val = EEPROM.read(addrbrightness);
  if (val != brightness) {
    EEPROM.write(addrbrightness, brightness);
  }
}

void LogicValues::restoreValuesFromEeprom()
{
  unsigned long valULong;
  uint16_t valUint16;
  uint8_t val;

  valULong = eepromReadULong(addrframeDelay);
  if (valULong >= 1 && valULong <= FRAME_DELAY_MAX) {
    frameDelay = valULong;
  }

  valULong = eepromReadULong(addrinitDelay);
  if (valULong >= 1 && valULong <= INIT_DELAY_MAX) {
    initDelay = valULong;
  }

  valUint16 = eepromReadUint16(addrrepeat);
  if (valUint16 >= 1 && valUint16 <= REPEAT_MAX) {
    repeat = valUint16;
  }

  valULong = eepromReadULong(addrrepeatDelay);
  if (valULong >= 1 && valULong <= REPEAT_DELAY_MAX) {
    repeatDelay = valULong;
  }

  valUint16 = eepromReadUint16(addrrepeatTimes);
  if (valULong >= 1 && valULong <= REPEAT_TIMES_MAX) {
    repeatTimes = valULong;
  }

  val = EEPROM.read(addrbrightness);
  if (val >= 1 && val <= BRIGHTNESS_MAX) {
    brightness = val;
  }
 
}

void LogicValues::resetValuesToDefault()
{
  frameDelay = DEFAULT_FRAME_DELAY;
  initDelay = DEFAULT_INIT_DELAY;
  repeat = DEFAULT_REPEAT;
  repeatDelay = DEFAULT_REPEAT_DELAY;
  repeatTimes = DEFAULT_REPEAT_TIMES;
  brightness = DEFAULT_BRIGHTNESS;

  storeValuesToEeprom();
}
  
uint16_t LogicValues::eepromReadUint16(uint8_t address) {
  uint16_t one = EEPROM.read(address);
  uint16_t two = EEPROM.read(address + 1);
  
  return ((one << 0) & 0xFF) + ((two << 8) & 0xFFFF);
}

void LogicValues::eepromWriteUint16(uint8_t address, unsigned long value) {
  byte two = (value & 0xFF);
  byte one = ((value >> 8) & 0xFF);
  
  EEPROM.write(address, one);
  EEPROM.write(address + 1, two);
}

unsigned long LogicValues::eepromReadULong(uint8_t address) {
  unsigned long one = EEPROM.read(address);
  unsigned long two = EEPROM.read(address + 1);
  unsigned long three = EEPROM.read(address + 2);
  unsigned long four = EEPROM.read(address + 3);
  
  return ((one << 0) & 0xFF) + ((two << 8) & 0xFFFF) + ((three << 16) & 0xFFFFFF) + ((four << 24) & 0xFFFFFFFF);
}

void LogicValues::eepromWriteULong(uint8_t address, unsigned long value) {
  byte one = (value & 0xFF);
  byte two = ((value >> 8) & 0xFF);
  byte three = ((value >> 16) & 0xFF);
  byte four = ((value >> 24) & 0xFF);
  
  EEPROM.write(address, one);
  EEPROM.write(address + 1, two);
  EEPROM.write(address + 2, three);
  EEPROM.write(address + 3, four);
}