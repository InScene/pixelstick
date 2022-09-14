/*
  Copyright Christian Mertens 2022
*/
#ifndef __STRIP_HANDLER_H__
#define __STRIP_HANDLER_H__

#include <Adafruit_NeoPixel.h>          // Library for the WS2812 Neopixel Strip

const uint8_t kStripLength = 144;       // Set the number of LEDs the LED Strip
// Pin assignments for the Arduino (Make changes to these if you use different Pins)
const uint8_t kNpPin = 6;               // Data Pin for the NeoPixel LED Strip

class StripHandler
{
  public:
    StripHandler();

    void Setup();
    void LatchAndDelay(unsigned long delayVal);
    // Note: change the order of r,g,b in the function if the correct colors are not displayed
    void SetPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    void Clear();

  private:
    Adafruit_NeoPixel strip_;

};

#endif // __STRIP_HANDLER_H__