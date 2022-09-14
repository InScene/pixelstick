/*
  Copyright Christian Mertens 2022
*/
#ifndef __FILE_STATES_H__
#define __FILE_STATES_H__

#include "global.h"

void s1_1_file_select()
{
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State s1_1_file_select");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileSelect, filehandler.GetFilename());
  }
}

void s1_1_1_now_playing() {
  FileHandler::ErrorCode fileError;
  const String filename = filehandler.GetFilename();
  const uint8_t brightness = logicValues.getBrightness();
  const unsigned long frameDelay = logicValues.getFrameDelay();

  display.Set(kMenuHeader, kMenuHeaderNowPlaying, filename);
  delay(logicValues.getInitDelay());
  uint16_t repeatTimes = logicValues.getRepeatTimes();
  if (repeatTimes > 1) {
    for (int x = repeatTimes; x > 0; x--) {
      fileError = filehandler.SendFile(filename, brightness, frameDelay);
      if(fileError != FileHandler::kNoError) {
        break;
      }
      delay(logicValues.getRepeatDelay());
    }
  }
  else {
    fileError = filehandler.SendFile(filename, brightness, frameDelay);
  }
  stripHandler.Clear();

  switch (fileError)
  {
  case FileHandler::kFileReadError:
    display.Set(kMenuHeader, kErrorHeader, "Error reading file");
    delay(1000);
    break;
  case FileHandler::kFileNotABitmap:
    display.Set(kMenuHeader, kErrorHeader, "not a bitmap");
    delay(1000);
    break;
  case FileHandler::kUnsupportedBitmap:
    display.Set(kMenuHeader, kErrorHeader, "Unsupported", "Bitmap Use 24bpp");
    delay(1000);
    break;
  
  default:
    break;
  }
}

void s1_1_2_next_file() {
  filehandler.SelectNextFile();
}

void s1_1_3_prev_file() {
  filehandler.SelectPreviousFile();
}

void s1_2_brightness(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State s1_2_brightness");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileBrightness,
                (uint16_t)logicValues.getBrightness(), kMenuFileBrightnessValue);
  }
}

void s1_2_1_brightness_inc(){
  logicValues.increaseBrightness();
}

void s1_2_2_brightness_dec(){
  logicValues.decreaseBrightness();
}

void s1_3_init_delay(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State s1_3_init_delay");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileInitDelay, 
                logicValues.getInitDelay(), kMenuFileInitDelayValue);
  }
}

void s1_3_1_init_delay_inc(){
  logicValues.increaseInitDelay1Sec();
}

void s1_3_2_init_delay_dec(){
  logicValues.decreaseInitDelay1Sec();
}

void s1_4_frame_delay(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State s1_4_frame_delay");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileFrameDelay, 
                logicValues.getFrameDelay(), kMenuFileFrameDelayValue);
  }
}

void s1_4_1_frame_delay_inc(){
  logicValues.increaseFrameDelay();
}

void s1_4_2_frame_delay_dec(){
  logicValues.decreaseFrameDelay();
}

void s1_5_repeat_times(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State s1_5_repeat_times");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileRepeatTimes,
                logicValues.getRepeatTimes());
  }
}

void s1_5_1_repeat_times_inc(){
  logicValues.increaseRepeatTimes();
}

void s1_5_2_repeat_times_dec(){
  logicValues.decreaseRepeatTimes();
}

void s1_6_repeat_delay(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State s1_6_repeat_delay");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileRepeatDelay, 
                logicValues.getRepeatDelay(), kMenuFileRepeatDelayValue);
  }
}

void s1_6_1_repeat_delay_inc(){
  logicValues.increaseRepeatDelay();
}

void s1_6_2_repeat_delay_dec(){
  logicValues.decreaseRepeatDelay();
}

void s1_7_reset_values(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State s1_7_reset_values");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileResetValue);
  }
}

void s1_7_1_reset_to_default(){
  logicValues.resetValuesToDefault();
  display.Set(kMenuHeader, kMenuFileHeader, kMenuValueResetted);
  delay(3000);
}

void s1_8_main_menu(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State s1_8_main_menu");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileMainMenu);
  }
}

/********************* Transitions ****************************/

bool transitionS1_1_to_S1() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}

bool transitionS1_1_to_S1_1_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kEnter){
    return true;
  }

  return false;
}

bool transitionS1_1_to_S1_1_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kRight){
    return true;
  }

  return false;
}

bool transitionS1_1_to_S1_1_3() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}


bool transitionS1_1_to_S1_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    return true;
  }

  return false;
}

bool transitionS1_1_to_S1_8() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    return true;
  }

  return false;
}
bool transitionS1_1_1_to_S1_1() {
  return true;
}

bool transitionS1_1_2_to_S1_1() {
  return true;
}

bool transitionS1_1_3_to_S1_1() {
  return true;
}


bool transitionS1_2_to_S1_2_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kRight){
    return true;
  }

  return false;
}

bool transitionS1_2_to_S1_2_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}

bool transitionS1_2_to_S1_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    logicValues.storeValuesToEeprom();
    return true;
  }

  return false;
}

bool transitionS1_2_to_S1_3() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    logicValues.storeValuesToEeprom();
    return true;
  }

  return false;
}

bool transitionS1_2_1_to_S1_2() {
  return true;
}

bool transitionS1_2_2_to_S1_2() {
  return true;
}


bool transitionS1_3_to_S1_3_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kRight){
    return true;
  }

  return false;
}

bool transitionS1_3_to_S1_3_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}

bool transitionS1_3_to_S1_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    logicValues.storeValuesToEeprom();
    return true;
  }

  return false;
}

bool transitionS1_3_to_S1_4() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    logicValues.storeValuesToEeprom();
    return true;
  }

  return false;
}

bool transitionS1_3_1_to_S1_3() {
  return true;
}

bool transitionS1_3_2_to_S1_3() {
  return true;
}


bool transitionS1_4_to_S1_4_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kRight){
    return true;
  }

  return false;
}

bool transitionS1_4_to_S1_4_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}

bool transitionS1_4_to_S1_3() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    logicValues.storeValuesToEeprom();
    return true;
  }

  return false;
}

bool transitionS1_4_to_S1_5() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    logicValues.storeValuesToEeprom();
    return true;
  }

  return false;
}

bool transitionS1_4_1_to_S1_4() {
  return true;
}

bool transitionS1_4_2_to_S1_4() {
  return true;
}


bool transitionS1_5_to_S1_5_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kRight){
    return true;
  }

  return false;
}

bool transitionS1_5_to_S1_5_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}

bool transitionS1_5_to_S1_4() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    logicValues.storeValuesToEeprom();
    return true;
  }

  return false;
}

bool transitionS1_5_to_S1_6() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    logicValues.storeValuesToEeprom();
    return true;
  }

  return false;
}

bool transitionS1_5_1_to_S1_5() {
  return true;
}

bool transitionS1_5_2_to_S1_5() {
  return true;
}


bool transitionS1_6_to_S1_6_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kRight){
    return true;
  }

  return false;
}

bool transitionS1_6_to_S1_6_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}

bool transitionS1_6_to_S1_5() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    logicValues.storeValuesToEeprom();
    return true;
  }

  return false;
}

bool transitionS1_6_to_S1_7() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    logicValues.storeValuesToEeprom();
    return true;
  }

  return false;
}

bool transitionS1_6_1_to_S1_6() {
  return true;
}

bool transitionS1_6_2_to_S1_6() {
  return true;
}


bool transitionS1_7_to_S1_8() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    return true;
  }

  return false;
}

bool transitionS1_7_to_S1_6() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    return true;
  }

  return false;
}

bool transitionS1_7_to_S1_7_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kEnter){
    return true;
  }

  return false;
}

bool transitionS1_7_1_to_S1_7() {
  return true;
}


bool transitionS1_8_to_S1_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    return true;
  }

  return false;
}

bool transitionS1_8_to_S1_7() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    return true;
  }

  return false;
}

bool transitionS1_8_to_S1() {
  if(keypad.GetLastReadedKey() == KeyPad::kEnter){
    return true;
  }

  return false;
}
#endif // __FILE_STATES_H__