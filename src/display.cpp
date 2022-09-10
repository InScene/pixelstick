/*
  Copyright Christian Mertens 2022
*/
#include "display.h"

Display::Display(Adafruit_SSD1306& lcd) :
  lcd(lcd)
{

}

Display::~Display()
{
  
}

void Display::setup()
{
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    //Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  lcd.display();
  delay(100);
}

void Display::set(const String& header, const String texts[], uint8_t sizeTexts)
{
  lcd.clearDisplay();
  lcd.setTextSize(2);
  lcd.setTextColor(SSD1306_WHITE);
  lcd.setCursor(0, 0);
  lcd.println(header);
  lcd.setTextSize(1);
  for(uint8_t i=0; i<sizeTexts; i++)
  {
    lcd.println(texts[i]);
  }
  lcd.display();
}

void Display::set(const String& header, const String& text, const String& text2, const uint16_t value)
{
  lcd.clearDisplay();
  lcd.setTextSize(2);
  lcd.setTextColor(SSD1306_WHITE);
  lcd.setCursor(0, 0);
  lcd.println(header);
  lcd.setTextSize(1);
  lcd.println(text);
  lcd.println(text2);
  lcd.print(F("Value: "));
  lcd.println(value);
  lcd.display();
}

void Display::set(const String& header, const String& text, const String& text2, const unsigned long value)
{
  lcd.clearDisplay();
  lcd.setTextSize(2);
  lcd.setTextColor(SSD1306_WHITE);
  lcd.setCursor(0, 0);
  lcd.println(header);
  lcd.setTextSize(1);
  lcd.println(text);
  lcd.println(text2);
  lcd.print(F("Value: "));
  lcd.println(value);
  lcd.display();
}

void Display::set(const String& header, const String& text, const String& text2)
{
  lcd.clearDisplay();
  lcd.setTextSize(2);
  lcd.setTextColor(SSD1306_WHITE);
  lcd.setCursor(0, 0);
  lcd.println(header);
  lcd.setTextSize(1);
  lcd.println(text);
  lcd.println(text2);
  lcd.display();
}
