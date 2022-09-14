/*
  Copyright Christian Mertens 2022
*/
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Adafruit_SSD1306.h>
#include "text_defines.h"

class Display
{
  public:
    const uint8_t kDisplayArraySizeMax  = 5;

    Display();
    ~Display();

    void Setup();
    void Set(const String& header, const String texts[], uint8_t sizeTexts);
    void Set(const String& header, const String& text, const String& text2, 
             const uint16_t value, const String text3 = "Value: ");   
    void Set(const String& header, const String& text, const String& text2, 
            const unsigned long value, const String text3 = "Value: ");
    void Set(const String& header, const String& text, const String text2 ="");
    void Set(const String& header, const String& text, const String& text2, 
             const String& text3);

  private:
    const uint8_t kScreenWidth = 128; // OLED display width, in pixels
    const uint8_t kScreenHeight = 64; // OLED display height, in pixels
    const int kOledReset = -1; // Reset pin # (or -1 if sharing Arduino reset pin)
    const uint16_t kTextColor = SSD1306_WHITE;

    Adafruit_SSD1306 lcd_;
};

#endif // __DISPLAY_H__