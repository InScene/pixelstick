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
