/*
  Copyright Christian Mertens 2022
*/
#ifndef __FILE_STATES_H__
#define __FILE_STATES_H__

#include "global.h"

void S1_1_FileSelect()
{
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State S1_1_FileSelect");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileSelect, filehandler.GetFilename());
  }
}

void S1_1_1_NowPlaying() {
  FileHandler::ErrorCode file_error;
  const String filename = filehandler.GetFilename();
  const uint8_t brightness = logicValues.GetBrightness();
  const unsigned long frame_delay = logicValues.GetFrameDelay();

  display.Set(kMenuHeader, kMenuHeaderNowPlaying, filename);
  delay(logicValues.GetInitDelay());
  uint16_t repeat_times = logicValues.GetRepeatTimes();
  if (repeat_times > 1) {
    for (int x = repeat_times; x > 0; x--) {
      file_error = filehandler.SendFile(filename, brightness, frame_delay);
      if(file_error != FileHandler::kNoError) {
        break;
      }
      delay(logicValues.GetRepeatDelay());
    }
  }
  else {
    file_error = filehandler.SendFile(filename, brightness, frame_delay);
  }
  stripHandler.Clear();

  switch (file_error)
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

void S1_1_2_NextFile() {
  filehandler.SelectNextFile();
}

void S1_1_3_PrevFile() {
  filehandler.SelectPreviousFile();
}

void S1_2_Brightness(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State S1_2_Brightness");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileBrightness,
                (uint16_t)logicValues.GetBrightness(), kMenuFileBrightnessValue);
  }
}

void S1_2_1_BrightnessInc(){
  logicValues.IncreaseBrightness();
}

void S1_2_2_BrightnessDec(){
  logicValues.DecreaseBrightness();
}

void S1_3_InitDelay(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State S1_3_InitDelay");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileInitDelay, 
                logicValues.GetInitDelay(), kMenuFileInitDelayValue);
  }
}

void S1_3_1_InitDelayInc(){
  logicValues.IncreaseInitDelay1Sec();
}

void S1_3_2_InitDelayDec(){
  logicValues.DecreaseInitDelay1Sec();
}

void S1_4_FrameDelay(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State S1_4_FrameDelay");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileFrameDelay, 
                logicValues.GetFrameDelay(), kMenuFileFrameDelayValue);
  }
}

void S1_4_1_FrameDelayInc(){
  logicValues.IncreaseFrameDelay();
}

void S1_4_2_FrameDelayDec(){
  logicValues.DecreaseFrameDelay();
}

void S1_5_RepeatTimes(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State S1_5_RepeatTimes");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileRepeatTimes,
                logicValues.GetRepeatTimes());
  }
}

void S1_5_1_RepeatTimesInc(){
  logicValues.IncreaseRepeatTimes();
}

void S1_5_2_RepeatTimesDec(){
  logicValues.DecreaseRepeatTimes();
}

void S1_6_RepeatDelay(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State S1_6_RepeatDelay");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileRepeatDelay, 
                logicValues.GetRepeatDelay(), kMenuFileRepeatDelayValue);
  }
}

void S1_6_1_RepeatDelayInc(){
  logicValues.IncreaseRepeatDelay();
}

void S1_6_2_RepeatDelayDec(){
  logicValues.DecreaseRepeatDelay();
}

void S1_7_ResetValues(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State S1_7_ResetValues");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileResetValue);
  }
}

void S1_7_1_ResetToDefault(){
  logicValues.ResetValuesToDefault();
  display.Set(kMenuHeader, kMenuFileHeader, kMenuValueResetted);
  delay(3000);
}

void S1_8_MainMenu(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State S1_8_MainMenu");
    #endif
    display.Set(kMenuHeader, kMenuFileHeader, kMenuFileMainMenu);
  }
}

/********************* TransitionS ****************************/

bool TransitionS1_1_to_S1() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}

bool TransitionS1_1_to_S1_1_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kEnter){
    return true;
  }

  return false;
}

bool TransitionS1_1_to_S1_1_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kRight){
    return true;
  }

  return false;
}

bool TransitionS1_1_to_S1_1_3() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}


bool TransitionS1_1_to_S1_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    return true;
  }

  return false;
}

bool TransitionS1_1_to_S1_8() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    return true;
  }

  return false;
}
bool TransitionS1_1_1_to_S1_1() {
  return true;
}

bool TransitionS1_1_2_to_S1_1() {
  return true;
}

bool TransitionS1_1_3_to_S1_1() {
  return true;
}


bool TransitionS1_2_to_S1_2_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kRight){
    return true;
  }

  return false;
}

bool TransitionS1_2_to_S1_2_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}

bool TransitionS1_2_to_S1_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    logicValues.StoreValuesToEeprom();
    return true;
  }

  return false;
}

bool TransitionS1_2_to_S1_3() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    logicValues.StoreValuesToEeprom();
    return true;
  }

  return false;
}

bool TransitionS1_2_1_to_S1_2() {
  return true;
}

bool TransitionS1_2_2_to_S1_2() {
  return true;
}


bool TransitionS1_3_to_S1_3_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kRight){
    return true;
  }

  return false;
}

bool TransitionS1_3_to_S1_3_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}

bool TransitionS1_3_to_S1_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    logicValues.StoreValuesToEeprom();
    return true;
  }

  return false;
}

bool TransitionS1_3_to_S1_4() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    logicValues.StoreValuesToEeprom();
    return true;
  }

  return false;
}

bool TransitionS1_3_1_to_S1_3() {
  return true;
}

bool TransitionS1_3_2_to_S1_3() {
  return true;
}


bool TransitionS1_4_to_S1_4_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kRight){
    return true;
  }

  return false;
}

bool TransitionS1_4_to_S1_4_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}

bool TransitionS1_4_to_S1_3() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    logicValues.StoreValuesToEeprom();
    return true;
  }

  return false;
}

bool TransitionS1_4_to_S1_5() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    logicValues.StoreValuesToEeprom();
    return true;
  }

  return false;
}

bool TransitionS1_4_1_to_S1_4() {
  return true;
}

bool TransitionS1_4_2_to_S1_4() {
  return true;
}


bool TransitionS1_5_to_S1_5_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kRight){
    return true;
  }

  return false;
}

bool TransitionS1_5_to_S1_5_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}

bool TransitionS1_5_to_S1_4() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    logicValues.StoreValuesToEeprom();
    return true;
  }

  return false;
}

bool TransitionS1_5_to_S1_6() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    logicValues.StoreValuesToEeprom();
    return true;
  }

  return false;
}

bool TransitionS1_5_1_to_S1_5() {
  return true;
}

bool TransitionS1_5_2_to_S1_5() {
  return true;
}


bool TransitionS1_6_to_S1_6_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kRight){
    return true;
  }

  return false;
}

bool TransitionS1_6_to_S1_6_2() {
  if(keypad.GetLastReadedKey() == KeyPad::kLeft){
    return true;
  }

  return false;
}

bool TransitionS1_6_to_S1_5() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    logicValues.StoreValuesToEeprom();
    return true;
  }

  return false;
}

bool TransitionS1_6_to_S1_7() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    logicValues.StoreValuesToEeprom();
    return true;
  }

  return false;
}

bool TransitionS1_6_1_to_S1_6() {
  return true;
}

bool TransitionS1_6_2_to_S1_6() {
  return true;
}


bool TransitionS1_7_to_S1_8() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    return true;
  }

  return false;
}

bool TransitionS1_7_to_S1_6() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    return true;
  }

  return false;
}

bool TransitionS1_7_to_S1_7_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kEnter){
    return true;
  }

  return false;
}

bool TransitionS1_7_1_to_S1_7() {
  return true;
}


bool TransitionS1_8_to_S1_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kDown){
    return true;
  }

  return false;
}

bool TransitionS1_8_to_S1_7() {
  if(keypad.GetLastReadedKey() == KeyPad::kUp){
    return true;
  }

  return false;
}

bool TransitionS1_8_to_S1() {
  if(keypad.GetLastReadedKey() == KeyPad::kEnter){
    return true;
  }

  return false;
}
#endif // __FILE_STATES_H__