/*
  Copyright Christian Mertens 2022
*/
#ifndef __TEXT_DEFINES_H__
#define __TEXT_DEFINES_H__

#include <Arduino.h>

#define LINES_COPYRIGHT 5
static String COPYRIGHT_TEXTS[LINES_COPYRIGHT] = {
  "(c) Christian Mertens 2022",
  "V1.2",
  " ",
  "..Initializing..",
  "   Please wait"
};

#define MENU_HEADER F("LIGHTY")
#define ERROR_HEADER F("ERROR")

#define MENU_MAIN_HEADER F("Main Menu ")
#define MENU_MAIN_FILE F("1:File ")

#define MENU_FILE_HEADER F("1:File ")
#define MENU_FILE_SELECT F("1:File Select ")
#define MENU_FILE_BRIGHTNESS F("2:Brightness ")
#define MENU_FILE_BRIGHTNESS_VALUE F("Value %: ")
#define MENU_FILE_INIT_DELAY F("3:Init Delay ")
#define MENU_FILE_INIT_DELAY_VALUE F("Value ms: ")
#define MENU_FILE_FRAME_DELAY F("4:Frame Delay")
#define MENU_FILE_FRAME_DELAY_VALUE F("Value ms: ")
#define MENU_FILE_REPEAT_TIMES F("5:Repeat Times")
#define MENU_FILE_REPEAT_DELAY F("6:Repeat Delay")
#define MENU_FILE_REPEAT_DELAY_VALUE F("Value ms: ")
#define MENU_FILE_RESET_VALUES F("7:Reset Values")
#define MENU_FILE_MAIN_MENU F("8:Main Menu")

#define MENU_HEADER_NOW_PLAYING F(" ")
#define MENU_NOW_PLAYING F("Now Playing")

#define MENU_VALUE_RESETTED F("Values resetted")

#endif // __TEXT_DEFINES_H__