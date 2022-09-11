/*
  Copyright Christian Mertens 2022
*/
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Adafruit_SSD1306.h>
#include "text_defines.h"

#define DISPLAY_ARRAY_SIZE_MAX 5
class Display
{
  public:
    Display();
    ~Display();

    void setup();
    void set(const String& header, const String texts[], uint8_t sizeTexts);
    void set(const String& header, const String& text, const String& text2, 
             const uint16_t value, const String text3 = "Value: ");   
    void set(const String& header, const String& text, const String& text2, 
            const unsigned long value, const String text3 = "Value: ");
    void set(const String& header, const String& text, const String text2 ="");
    void set(const String& header, const String& text, const String& text2, 
             const String& text3);

  private:
    Adafruit_SSD1306 lcd;
};

#endif // __DISPLAY_H__