/*
  Copyright Christian Mertens 2022
*/
#include "display.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Display::Display() :
  lcd(Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET))
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

  // Clear display buffer because
  // the library initializes this with an Adafruit splash screen.
  lcd.clearDisplay();
  lcd.display();
  delay(100);
}

void Display::set(const String& header, const String texts[], uint8_t sizeTexts)
{
  if(sizeTexts > DISPLAY_ARRAY_SIZE_MAX) {
    sizeTexts = DISPLAY_ARRAY_SIZE_MAX;
  }

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

void Display::set(const String& header, const String& text, const String& text2, 
                  const uint16_t value, const String text3)
{
  lcd.clearDisplay();
  lcd.setTextSize(2);
  lcd.setTextColor(SSD1306_WHITE);
  lcd.setCursor(0, 0);
  lcd.println(header);
  lcd.setTextSize(1);
  lcd.println(text);
  lcd.println(text2);
  lcd.print(text3);
  lcd.println(value);
  lcd.display();
}

void Display::set(const String& header, const String& text, const String& text2, 
                  const unsigned long value, const String text3)
{
  lcd.clearDisplay();
  lcd.setTextSize(2);
  lcd.setTextColor(SSD1306_WHITE);
  lcd.setCursor(0, 0);
  lcd.println(header);
  lcd.setTextSize(1);
  lcd.println(text);
  lcd.println(text2);
  lcd.print(text3);
  lcd.println(value);
  lcd.display();
}

void Display::set(const String& header, const String& text, const String text2)
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

void Display::set(const String& header, const String& text, const String& text2, const String& text3)
{
  lcd.clearDisplay();
  lcd.setTextSize(2);
  lcd.setTextColor(SSD1306_WHITE);
  lcd.setCursor(0, 0);
  lcd.println(header);
  lcd.setTextSize(1);
  lcd.println(text);
  lcd.println(text2);
  lcd.println(text3);
  lcd.display();
}