/*
  Copyright Christian Mertens 2022
*/
#ifndef __TEXT_DEFINES_H__
#define __TEXT_DEFINES_H__

#include <Arduino.h>

const uint8_t kLinesCopyright = 5;
const String kCopyrightTexts[kLinesCopyright] = {
  "(c) Christian Mertens 2022",
  "V1.2",
  " ",
  "..Initializing..",
  "   Please wait"
};

const String kMenuHeader = "LIGHTY";
const String kErrorHeader = "ERROR";

const String kMenuMainHeader = "Main Menu ";
const String kMenuMainFile = "1:File ";

const String kMenuFileHeader = "1:File ";
const String kMenuFileSelect = "1:File Select ";
const String kMenuFileBrightness = "2:Brightness ";
const String kMenuFileBrightnessValue = "Value %: ";
const String kMenuFileInitDelay = "3:Init Delay ";
const String kMenuFileInitDelayValue = "Value ms: ";
const String kMenuFileFrameDelay =  "4:Frame Delay";
const String kMenuFileFrameDelayValue = "Value ms: ";
const String kMenuFileRepeatTimes = "5:Repeat Times";
const String kMenuFileRepeatDelay = "6:Repeat Delay";
const String kMenuFileRepeatDelayValue = "Value ms: ";
const String kMenuFileResetValue =  "7:Reset Values";
const String kMenuFileMainMenu = "8:Main Menu";

const String kMenuHeaderNowPlaying = " ";
const String kMenuNowPlaying = "Now Playing";

const String kMenuValueResetted = "Values resetted";

#endif // __TEXT_DEFINES_H__