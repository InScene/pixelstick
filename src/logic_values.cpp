/*
  Copyright Christian Mertens 2022
*/
#include "logic_values.h"

#define ULONG_MAX 0xFFFFFFFF
#define OneSecInMs 1000
#define OneHundredMs 100
#define BRIGHTNESS_MAX 100

LogicValues::LogicValues() :
  frameDelay(15),
  initDelay(0),
  repeat(0),
  repeatDelay(0),
  repeatTimes(1),
  brightness(50)
{
  
}

unsigned long  LogicValues::getFrameDelay() const
{
  return frameDelay;
}

void LogicValues::increaseFrameDelay()
{
  if(frameDelay < ULONG_MAX)
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
  if(initDelay <= (ULONG_MAX-OneSecInMs))
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
  if(repeat < (UINT16_MAX))
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
  if(repeatDelay <= (ULONG_MAX-OneHundredMs))
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
  if(repeatTimes < (UINT16_MAX))
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
  