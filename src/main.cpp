/*
  DIY Lighty + SD + OLED + 5 way joystick + WS2812B RGB LED
  Christian Mertens 2022
  based on pixelstick by Dirk Essl 2020
  based on Digital Light Wand by Michael Ross

  Lighty is for use in specialized Light Painting Photography
  Applications.

  The functionality that is included in this code is as follows:

  Menu System
  1 - File select
  2 - Brightness
  3 - Initial Delay
  4 - Frame Delay
  5 - Repeat Times (The number of times to repeat the current file playback)
  6 - Repeat Delay (if you want a delay between repeated files)

  This code supports direct reading of a 24bit Windows BMP from the SD card.
  BMP images must be rotated 90 degrees clockwise and the width of the image should match the
  number of pixels you have on your LED strip.  The bottom of the tool will be the INPUT
  end of the strips where the Arduino is connected and will be the left side of the input
  BMP image.

  Mick also added a Gamma Table from adafruit code which gives better conversion of 24 bit to
  21 bit coloring.
*/

// Library initialization
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <SoftwareReset.hpp>
#include "global.h"
#include "state_machine_logic.h"

// Setup loop to get everything ready.  This is only run once at power on or reset
void setup() {

   //Serial.begin(9600);

  logicValues.restoreValuesFromEeprom();
  
  display.Setup();
  
  // Print copyright on display
  display.Set(kMenuHeader, kCopyrightTexts, kLinesCopyright);
  delay(3000);
  
  keypad.setup();

  stripHandler.Setup();
  
  if(!filehandler.Setup()) {
    // On error display error msg and reset arduino
    display.Set(kMenuHeader, kErrorHeader, "SD init failed! ", "Automatically  reboot");
    delay(3000);
    softwareReset::standard();
  } else {
    display.Set(kMenuHeader, "SD init done.   ");
    delay(1000);
  }

  display.Set(kMenuHeader, "Scanning files  ");
  delay(500);
  filehandler.ScanForFiles();

  stripHandler.Clear();

  state_machine_setup();
}

// The Main Loop for the program starts here...
// This will loop endlessly looking for a key press to perform a function
void loop() {
  keypad.read();
  machine.run();
  delay(500);
}
