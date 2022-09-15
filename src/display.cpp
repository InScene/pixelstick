/*
  Copyright Christian Mertens 2022
*/
#include "display.h"

Display::Display() :
  lcd_(Adafruit_SSD1306(kScreenWidth, kScreenHeight, &Wire, kOledReset))
{

}

Display::~Display()
{
  
}

void Display::Setup()
{
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!lcd_.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    //Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Clear display buffer because the library initializes this with an Adafruit splash screen.
  lcd_.clearDisplay();
  lcd_.display();
  delay(100);
}

void Display::Set(const String& header, const char* const texts[], uint8_t sizeTexts)
{
  if(sizeTexts > kDisplayArraySizeMax) {
    sizeTexts = kDisplayArraySizeMax;
  }

  lcd_.clearDisplay();
  lcd_.setTextSize(2);
  lcd_.setTextColor(kTextColor);
  lcd_.setCursor(0, 0);
  lcd_.println(header);
  lcd_.setTextSize(1);
  for(uint8_t i=0; i<sizeTexts; i++)
  {
    lcd_.println(texts[i]);
  }
  lcd_.display();
}

void Display::Set(const String& header, const String& text, const String& text2, 
                  const uint16_t value, const String text3)
{
  lcd_.clearDisplay();
  lcd_.setTextSize(2);
  lcd_.setTextColor(kTextColor);
  lcd_.setCursor(0, 0);
  lcd_.println(header);
  lcd_.setTextSize(1);
  lcd_.println(text);
  lcd_.println(text2);
  lcd_.print(text3);
  lcd_.println(value);
  lcd_.display();
}

void Display::Set(const String& header, const String& text, const String& text2, 
                  const unsigned long value, const String text3)
{
  lcd_.clearDisplay();
  lcd_.setTextSize(2);
  lcd_.setTextColor(kTextColor);
  lcd_.setCursor(0, 0);
  lcd_.println(header);
  lcd_.setTextSize(1);
  lcd_.println(text);
  lcd_.println(text2);
  lcd_.print(text3);
  lcd_.println(value);
  lcd_.display();
}

void Display::Set(const String& header, const String& text, const String text2)
{
  lcd_.clearDisplay();
  lcd_.setTextSize(2);
  lcd_.setTextColor(kTextColor);
  lcd_.setCursor(0, 0);
  lcd_.println(header);
  lcd_.setTextSize(1);
  lcd_.println(text);
  lcd_.println(text2);
  lcd_.display();
}

void Display::Set(const String& header, const String& text, const String& text2, const String& text3)
{
  lcd_.clearDisplay();
  lcd_.setTextSize(2);
  lcd_.setTextColor(kTextColor);
  lcd_.setCursor(0, 0);
  lcd_.println(header);
  lcd_.setTextSize(1);
  lcd_.println(text);
  lcd_.println(text2);
  lcd_.println(text3);
  lcd_.display();
}