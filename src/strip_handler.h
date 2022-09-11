/*
  Copyright Christian Mertens 2022
*/
#ifndef __STRIP_HANDLER_H__
#define __STRIP_HANDLER_H__

#include <Adafruit_NeoPixel.h>           // Library for the WS2812 Neopixel Strip

#define STRIP_LENGTH 144                  // Set the number of LEDs the LED Strip
// Pin assignments for the Arduino (Make changes to these if you use different Pins)
#define NPPIN 6                            // Data Pin for the NeoPixel LED Strip

class StripHandler
{
  public:
    StripHandler();

    void setup();
    void latchanddelay(unsigned long delayVal);
    // Note: change the order of r,g,b in the function if the correct colors are not displayed
    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    void clear();

  private:
    Adafruit_NeoPixel strip;

};

#endif // __STRIP_HANDLER_H__