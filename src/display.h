/*
  Copyright Christian Mertens 2022
*/
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Adafruit_SSD1306.h>

#define MENU_HEADER F("LIGHTY")

#define MENU_MAIN_HEADER F("Main Menu ")
#define MENU_MAIN_FILE F("1:File ")

#define MENU_FILE_HEADER F("1:File ")
#define MENU_FILE_SELECT F("1_1:File Select ")
#define MENU_FILE_BRIGHTNESS F("1_2:Brightness ")
#define MENU_FILE_INIT_DELAY F("1_3:Init Delay ")
#define MENU_FILE_FRAME_DELAY F("1_4:Frame Delay")
#define MENU_FILE_REPEAT_TIMES F("1_5:Repeat Times")
#define MENU_FILE_REPEAT_DELAY F("1_6:Repeat Delay")
#define MENU_FILE_MAIN_MENU F("1_7:Main Menu")

#define MENU_HEADER_NOW_PLAYING F(" ")
#define MENU_NOW_PLAYING F("Now Playing")

class Display
{
  public:
    Display(Adafruit_SSD1306& lcd);
    ~Display();

    void set(const String& header, const String& text, const int value);
    void set(const String& header, const String& text, const String& text2);

  private:
    Adafruit_SSD1306& lcd;
};

#endif // __DISPLAY_H__