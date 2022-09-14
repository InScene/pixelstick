/*
  Copyright Christian Mertens 2022
*/

#include "strip_handler.h"

StripHandler::StripHandler() : 
  strip_(Adafruit_NeoPixel(kStripLength, kNpPin, NEO_GRB + NEO_KHZ800))
{
  
}

void StripHandler::Setup()
{
  strip_.begin();
  strip_.show();
}

void StripHandler::LatchAndDelay(unsigned long delayVal)
{
  strip_.show();
  delay(delayVal);
}

void StripHandler::SetPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{
  // Note:
  // The x,r,b,g sequence below might need to be changed if your strip is displaying
  // incorrect colors.  Some strips use an x,r,b,g sequence and some use x,r,g,b
  // Change the order if needed to make the colors correct.
  strip_.setPixelColor(n, r, b, g);
}

void StripHandler::Clear()
{
  for (uint8_t x = 0; x < kStripLength; x++) {
    strip_.setPixelColor(x, 0);
  }
  strip_.show();
}
