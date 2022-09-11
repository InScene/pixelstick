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
#include <EEPROM.h>
#include "global.h"
#include "state_machine_logic.h"

#define LINES_COPYRIGHT 5
String COPYRIGHT_TEXTS[LINES_COPYRIGHT] = {
  "(c) Christian Mertens 2022",
  "V1.1",
  " ",
  "..Initializing..",
  "   Please wait"
};


// EEPROM setup. saves all values in eeprom. the mega has 4kb of eeprom storage
// the current address in the EEPROM (i.e. which byte we're going to write to next)

// set addresses for save
int addrframeDelay = 0;                        // default for the frame delay
int addrinitDelay = 20;                        // Variable for delay between button press and start of light sequence
int addrrepeat = 30;                           // Variable to select auto repeat (until select button is pressed again)
int addrrepeatDelay = 400;                     // Variable for delay between repeats
int addrupdateMode = 50;                       // Variable to keep track of update Modes
int addrrepeatTimes = 60;                      // Variable to keep track of number of repeats
int addrbrightness = 70;                       // Variable and default for the Brightness of the strip


// Setup loop to get everything ready.  This is only run once at power on or reset
void setup() {

  // check if values in eeprom make sense, otherwise set default value
  if (EEPROM.read(addrbrightness) >= 1 && EEPROM.read(addrbrightness) <= 100) {
    logicValues.setBrightness((uint8_t)EEPROM.read(addrbrightness));
  } else {
    logicValues.setBrightness(50);
  }

  /*
    if (EEPROM.read(addrrepeatTimes) >= 1 && EEPROM.read(addrrepeatTimes) <= 100) {
      repeatTimes = EEPROM.read(addrrepeatTimes);
    } else {
      repeatTimes = 1;
    }

    if (EEPROM.read(addrrepeatDelay) >= 0 && EEPROM.read(addrrepeatDelay) <= 10000) {
      repeatDelay = EEPROM.read(addrrepeatDelay);
    } else {
      repeatDelay = 0;
    }
  */

  Serial.begin(9600);

  display.setup();
  Serial.println(LINES_COPYRIGHT);
  // Print copyright on display
  display.set(MENU_HEADER, COPYRIGHT_TEXTS, LINES_COPYRIGHT);
  delay(3000);
  
  keypad.setup();

  stripHandler.setup();
  
  if(!filehandler.setup()) {
    display.set(MENU_HEADER, ERROR_HEADER, "SD init failed! ");
    delay(2000);
  } else {
    display.set(MENU_HEADER, "SD init done.   ");
    delay(1000);
  }

  display.set(MENU_HEADER, "Scanning files  ");
  delay(500);
  filehandler.scanForFiles();

  stripHandler.clear();

  state_machine_setup();
}

// The Main Loop for the program starts here...
// This will loop endlessly looking for a key press to perform a function
void loop() {
  keypad.read();
  machine.run();
  delay(500);
}
