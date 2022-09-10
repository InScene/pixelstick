/*
  Copyright Christian Mertens 2022
*/

#include "strip_handler.h"

StripHandler::StripHandler() : 
  strip(Adafruit_NeoPixel(STRIP_LENGTH, NPPIN, NEO_GRB + NEO_KHZ800))
{
  
}

void StripHandler::setup()
{
  strip.begin();
  strip.show();
}

void StripHandler::latchanddelay(unsigned long delayVal)
{
  strip.show();
  delay(delayVal);
}

void StripHandler::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{
  // Note:
  // The x,r,b,g sequence below might need to be changed if your strip is displaying
  // incorrect colors.  Some strips use an x,r,b,g sequence and some use x,r,g,b
  // Change the order if needed to make the colors correct.
  strip.setPixelColor(n, r, b, g);
}

void StripHandler::clear()
{
  int x;
  for (x = 0; x < STRIP_LENGTH; x++) {
    strip.setPixelColor(x, 0);
  }
  strip.show();
}
