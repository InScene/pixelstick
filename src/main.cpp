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
#include "main.h"

FileHandler filehandler = FileHandler();


String COPYRIGHT_TEXTS[5] = {
  "(c) Christian Mertens 2022",
  "V1.1",
  " ",
  "..Initializing..",
  "Please wait"
};


// Intial Variable declarations and assignments (Make changes to these if you want to change defaults)

int frameDelay = 15;                      // default for the frame delay
int menuItem = 1;                         // Variable for current main menu selection
int initDelay = 0;                        // Variable for delay between button press and start of light sequence
int repeatDelay = 0;                      // Variable for delay between repeats
int repeatTimes = 1;                      // Variable to keep track of number of repeats
int brightness = 50;                      // Variable and default for the Brightness of the strip

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

  keypad.setup();

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
  // Print copyright on display
  display.set(MENU_HEADER, COPYRIGHT_TEXTS, sizeof(COPYRIGHT_TEXTS));

  delay(1000);

  stripHandler.setup();
  filehandler.setup();
  stripHandler.clear();

  state_machine_setup();
}

// The Main Loop for the program starts here...
// This will loop endlessly looking for a key press to perform a function
void loop() {
  keypad.read();
  machine.run();
  delay(250);
}

// The Main Loop for the program starts here...
// This will loop endlessly looking for a key press to perform a function
void loop_origin() {

  switch (menuItem) {
    case 1:
      lcd.clearDisplay();
      lcd.setTextSize(2);
      lcd.setTextColor(SSD1306_WHITE);
      lcd.setCursor(0, 0);
      lcd.println(F("LIGHTY"));
      lcd.setTextSize(1);
      lcd.println(F("1:File Select "));
      lcd.println(filehandler.getFilename());
      lcd.display();
      break;
    case 2:
      lcd.clearDisplay();
      lcd.setTextSize(2);
      lcd.setTextColor(SSD1306_WHITE);
      lcd.setCursor(0, 0);
      lcd.println(F("LIGHTY"));
      lcd.setTextSize(1);
      lcd.println(F("2:Brightness "));
      lcd.println(brightness);
      lcd.display();
      break;
    case 3:
      lcd.clearDisplay();
      lcd.setTextSize(2);
      lcd.setTextColor(SSD1306_WHITE);
      lcd.setCursor(0, 0);
      lcd.println(F("LIGHTY"));
      lcd.setTextSize(1);
      lcd.println(F("3:Init Delay "));
      lcd.println(initDelay);
      lcd.display();
      break;
    case 4:
      lcd.clearDisplay();
      lcd.setTextSize(2);
      lcd.setTextColor(SSD1306_WHITE);
      lcd.setCursor(0, 0);
      lcd.println(F("LIGHTY"));
      lcd.setTextSize(1);
      lcd.println(F("4:Frame Delay"));
      lcd.println(frameDelay);
      lcd.display();
      break;
    case 5:
      lcd.clearDisplay();
      lcd.setTextSize(2);
      lcd.setTextColor(SSD1306_WHITE);
      lcd.setCursor(0, 0);
      lcd.println(F("LIGHTY"));
      lcd.setTextSize(1);
      lcd.println(F("5:Repeat Times"));
      lcd.println(repeatTimes);
      lcd.display();
      break;
    case 6:
      lcd.clearDisplay();
      lcd.setTextSize(2);
      lcd.setTextColor(SSD1306_WHITE);
      lcd.setCursor(0, 0);
      lcd.println(F("LIGHTY"));
      lcd.setTextSize(1);
      lcd.println(F("6:Repeat Delay"));
      lcd.println(repeatDelay);
      lcd.display();
      break;
  }

  int keypress = keypad.read();
  delay(50);

  if (keypress == 4) {   // The select key was pressed

    lcd.clearDisplay();
    lcd.setTextSize(2);
    lcd.setTextColor(SSD1306_WHITE);
    lcd.setCursor(0, 0);
    lcd.println(F(" "));
    lcd.setTextSize(1);
    lcd.println(F("Now Playing"));
    lcd.println(filehandler.getFilename());
    lcd.display();
    delay(initDelay);
    if (repeatTimes > 1) {
      for (int x = repeatTimes; x > 0; x--) {
        filehandler.sendFile(filehandler.getFilename());
        delay(repeatDelay);
      }
    }
    else {
      filehandler.sendFile(filehandler.getFilename());
    }
    stripHandler.clear();
  }
  if (keypress == 0) {                    // The Right Key was Pressed
    switch (menuItem) {
      case 1:                             // Select the Next File
        //BackLightOn();
        filehandler.selectNextFile();
        DisplayCurrentFilename();
        break;
      case 2:                             // Adjust Brightness
        if (brightness < 100) {
          brightness += 1;
        }
        break;
      case 3:                             // Adjust Initial Delay + 1 second
        initDelay += 1000;
        break;
      case 4:                             // Adjust Frame Delay + 1 milliseconds
        frameDelay += 1;
        break;
      case 5:                             // Adjust Repeat Times + 1
        repeatTimes += 1;
        break;
      case 6:                             // Adjust Repeat Delay + 100 milliseconds
        repeatDelay += 100;
        break;
    }
  }

  if (keypress == 3) {                    // The Left Key was Pressed
    switch (menuItem) {                   // Select the Previous File
      case 1:
        //BackLightOn();
        filehandler.selectPreviousFile();
        DisplayCurrentFilename();
        delay(500);
        break;
      case 2:                             // Adjust Brightness
        //BackLightOn();
        if (brightness > 1) {
          brightness -= 1;
          EEPROM.put(addrbrightness, brightness);
        }
        break;
      case 3:                             // Adjust Initial Delay - 1 second
        if (initDelay > 0) {
          initDelay -= 1000;
          EEPROM.put(addrinitDelay, initDelay);
        }
        break;
      case 4:                             // Adjust Frame Delay - 1 millisecond
        if (frameDelay > 0) {
          frameDelay -= 1;
          EEPROM.put(addrframeDelay, frameDelay);
        }
        break;
      case 5:                             // Adjust Repeat Times - 1
        if (repeatTimes > 1) {
          repeatTimes -= 1;
          EEPROM.put(addrrepeatTimes, repeatTimes);
        }
        break;
      case 6:                             // Adjust Repeat Delay - 100 milliseconds
        if (repeatDelay > 0) {
          repeatDelay -= 100;
          EEPROM.put(addrrepeatDelay, repeatDelay);
        }
        break;
    }
  }

  //if (digitalRead(uppin) == LOW) key = 1;
  if (digitalRead(UPPIN) == LOW) {                 // The up key was pressed
    delay(50);
    if (menuItem == 1) {
      menuItem = 6;
    }
    else {
      menuItem -= 1;
    }
  }
  if (( keypress == 2)) {                 // The down key was pressed
    if (menuItem == 6) {
      menuItem = 1;
    }
    else {
      menuItem += 1;
    }
  }
}

void DisplayCurrentFilename() {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(filehandler.getFilename());
}
