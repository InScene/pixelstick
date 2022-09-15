/*
  Copyright Christian Mertens 2022
*/
#ifndef __TEXT_DEFINES_H__
#define __TEXT_DEFINES_H__

#include <Arduino.h>

const uint8_t kLinesCopyright = 5;
static const char* const kCopyrightTexts[kLinesCopyright] = {
  "(c) Christian Mertens 2022",
  "V1.2",
  " ",
  "..Initializing..",
  "   Please wait"
};

static const char* const kMenuHeader = "LIGHTY";
static const char* const kErrorHeader = "ERROR";

static const char* const kMenuMainHeader = "Main Menu ";
static const char* const kMenuMainFile = "1:File ";

static const char* const kMenuFileHeader = "1:File ";
static const char* const kMenuFileSelect = "1:File Select ";
static const char* const kMenuFileBrightness = "2:Brightness ";
static const char* const kMenuFileBrightnessValue = "Value %: ";
static const char* const kMenuFileInitDelay = "3:Init Delay ";
static const char* const kMenuFileInitDelayValue = "Value ms: ";
static const char* const kMenuFileFrameDelay =  "4:Frame Delay";
static const char* const kMenuFileFrameDelayValue = "Value ms: ";
static const char* const kMenuFileRepeatTimes = "5:Repeat Times";
static const char* const kMenuFileRepeatDelay = "6:Repeat Delay";
static const char* const kMenuFileRepeatDelayValue = "Value ms: ";
static const char* const kMenuFileResetValue =  "7:Reset Values";
static const char* const kMenuFileMainMenu = "8:Main Menu";

static const char* const kMenuHeaderNowPlaying = " ";
static const char* const kMenuNowPlaying = "Now Playing";

static const char* const kMenuValueResetted = "Values resetted";

#endif // __TEXT_DEFINES_H__