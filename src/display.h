/*
  Copyright Christian Mertens 2022
*/
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Adafruit_SSD1306.h>

#define MENU_HEADER F("LIGHTY")
#define ERROR_HEADER F("ERROR")

#define MENU_MAIN_HEADER F("Main Menu ")
#define MENU_MAIN_FILE F("1:File ")

#define MENU_FILE_HEADER F("1:File ")
#define MENU_FILE_SELECT F("1:File Select ")
#define MENU_FILE_BRIGHTNESS F("2:Brightness ")
#define MENU_FILE_INIT_DELAY F("3:Init Delay ")
#define MENU_FILE_FRAME_DELAY F("4:Frame Delay")
#define MENU_FILE_REPEAT_TIMES F("5:Repeat Times")
#define MENU_FILE_REPEAT_DELAY F("6:Repeat Delay")
#define MENU_FILE_RESET_VALUES F("7:Reset Values")
#define MENU_FILE_MAIN_MENU F("8:Main Menu")

#define MENU_HEADER_NOW_PLAYING F(" ")
#define MENU_NOW_PLAYING F("Now Playing")

#define MENU_VALUE_RESETTED F("Values resetted")

#define DISPLAY_ARRAY_SIZE_MAX 5
class Display
{
  public:
    Display();
    ~Display();

    void setup();
    void set(const String& header, const String texts[], uint8_t sizeTexts);
    void set(const String& header, const String& text, const String& text2, const uint16_t value);
    void set(const String& header, const String& text, const String& text2, const unsigned long value);
    void set(const String& header, const String& text, const String text2 = "");
    void set(const String& header, const String& text, const String& text2, const String& text3);

  private:
    Adafruit_SSD1306 lcd;
};

#endif // __DISPLAY_H__