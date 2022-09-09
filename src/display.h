/*
  Copyright Christian Mertens 2022
*/
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Adafruit_SSD1306.h>

#define MENU_HEADER_ITEM F("LIGHTY")
#define MENU_HEADER_NOW_PLAYING F(" ")
#define MENU_FILE_SELECT F("1:File Select ")
#define MENU_BRIGHTNESS F("2:Brightness ")
#define MENU_INIT_DELAY F("3:Init Delay ")
#define MENU_FRAME_DELAY F("4:Frame Delay")
#define MENU_REPEAT_TIMES F("5:Repeat Times")
#define MENU_REPEAT_DELAY F("6:Repeat Delay")
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