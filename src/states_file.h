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
    display.set(MENU_HEADER, MENU_FILE_HEADER, MENU_FILE_SELECT, filehandler.getFilename());
  }
}

void s1_1_1_now_playing() {
  FileHandler::ErrorCode fileError;
  const String filename = filehandler.getFilename();
  const uint8_t brightness = logicValues.getBrightness();
  const unsigned long frameDelay = logicValues.getFrameDelay();

  display.set(MENU_HEADER, MENU_HEADER_NOW_PLAYING, filename);
  delay(logicValues.getInitDelay());
  uint16_t repeatTimes = logicValues.getRepeatTimes();
  if (repeatTimes > 1) {
    for (int x = repeatTimes; x > 0; x--) {
      fileError = filehandler.sendFile(filename, brightness, frameDelay);
      if(fileError != FileHandler::NO_ERROR) {
        break;
      }
      delay(logicValues.getRepeatDelay());
    }
  }
  else {
    fileError = filehandler.sendFile(filename, brightness, frameDelay);
  }
  stripHandler.clear();

  switch (fileError)
  {
  case FileHandler::FILE_READ_ERROR:
    display.set(MENU_HEADER, ERROR_HEADER, "Error reading file");
    delay(1000);
    break;
  case FileHandler::FILE_NOT_A_BITMAP:
    display.set(MENU_HEADER, ERROR_HEADER, "not a bitmap");
    delay(1000);
    break;
  case FileHandler::UNSUPPORTED_BITMAP:
    display.set(MENU_HEADER, ERROR_HEADER, "Unsupported", "Bitmap Use 24bpp");
    delay(1000);
    break;
  
  default:
    break;
  }
}

void s1_1_2_next_file() {
  filehandler.selectNextFile();
}

void s1_1_3_prev_file() {
  filehandler.selectPreviousFile();
}

void s1_2_brightness(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State s1_2_brightness");
    #endif
    display.set(MENU_HEADER, MENU_FILE_HEADER, MENU_FILE_BRIGHTNESS, (uint16_t)logicValues.getBrightness());
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
    display.set(MENU_HEADER, MENU_FILE_HEADER, MENU_FILE_INIT_DELAY, logicValues.getInitDelay());
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
    display.set(MENU_HEADER, MENU_FILE_HEADER, MENU_FILE_FRAME_DELAY, logicValues.getFrameDelay());
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
    display.set(MENU_HEADER, MENU_FILE_HEADER, MENU_FILE_REPEAT_TIMES, logicValues.getRepeatTimes());
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
    display.set(MENU_HEADER, MENU_FILE_HEADER, MENU_FILE_REPEAT_DELAY, logicValues.getRepeatDelay());
  }
}

void s1_6_1_repeat_delay_inc(){
  logicValues.increaseRepeatDelay();
}

void s1_6_2_repeat_delay_dec(){
  logicValues.decreaseRepeatDelay();
}

void s1_7_main_menu(){
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State s1_7_main_menu");
    #endif
    display.set(MENU_HEADER, MENU_FILE_HEADER, MENU_FILE_MAIN_MENU);
  }
}

bool transitionS1_1_to_S1() {
  if(keypad.getLastReadedKey() == KeyPad::key_left){
    return true;
  }

  return false;
}

bool transitionS1_1_to_S1_1_1() {
  if(keypad.getLastReadedKey() == KeyPad::key_enter){
    return true;
  }

  return false;
}

bool transitionS1_1_to_S1_1_2() {
  if(keypad.getLastReadedKey() == KeyPad::key_right){
    return true;
  }

  return false;
}

bool transitionS1_1_to_S1_1_3() {
  if(keypad.getLastReadedKey() == KeyPad::key_left){
    return true;
  }

  return false;
}


bool transitionS1_1_to_S1_2() {
  if(keypad.getLastReadedKey() == KeyPad::key_down){
    return true;
  }

  return false;
}

bool transitionS1_1_to_S1_7() {
  if(keypad.getLastReadedKey() == KeyPad::key_up){
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
  if(keypad.getLastReadedKey() == KeyPad::key_right){
    return true;
  }

  return false;
}

bool transitionS1_2_to_S1_2_2() {
  if(keypad.getLastReadedKey() == KeyPad::key_left){
    return true;
  }

  return false;
}

bool transitionS1_2_to_S1_1() {
  if(keypad.getLastReadedKey() == KeyPad::key_up){
    return true;
  }

  return false;
}

bool transitionS1_2_to_S1_3() {
  if(keypad.getLastReadedKey() == KeyPad::key_down){
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
  if(keypad.getLastReadedKey() == KeyPad::key_right){
    return true;
  }

  return false;
}

bool transitionS1_3_to_S1_3_2() {
  if(keypad.getLastReadedKey() == KeyPad::key_left){
    return true;
  }

  return false;
}

bool transitionS1_3_to_S1_2() {
  if(keypad.getLastReadedKey() == KeyPad::key_up){
    return true;
  }

  return false;
}

bool transitionS1_3_to_S1_4() {
  if(keypad.getLastReadedKey() == KeyPad::key_down){
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
  if(keypad.getLastReadedKey() == KeyPad::key_right){
    return true;
  }

  return false;
}

bool transitionS1_4_to_S1_4_2() {
  if(keypad.getLastReadedKey() == KeyPad::key_left){
    return true;
  }

  return false;
}

bool transitionS1_4_to_S1_3() {
  if(keypad.getLastReadedKey() == KeyPad::key_up){
    return true;
  }

  return false;
}

bool transitionS1_4_to_S1_5() {
  if(keypad.getLastReadedKey() == KeyPad::key_down){
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
  if(keypad.getLastReadedKey() == KeyPad::key_right){
    return true;
  }

  return false;
}

bool transitionS1_5_to_S1_5_2() {
  if(keypad.getLastReadedKey() == KeyPad::key_left){
    return true;
  }

  return false;
}

bool transitionS1_5_to_S1_4() {
  if(keypad.getLastReadedKey() == KeyPad::key_up){
    return true;
  }

  return false;
}

bool transitionS1_5_to_S1_6() {
  if(keypad.getLastReadedKey() == KeyPad::key_down){
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
  if(keypad.getLastReadedKey() == KeyPad::key_right){
    return true;
  }

  return false;
}

bool transitionS1_6_to_S1_6_2() {
  if(keypad.getLastReadedKey() == KeyPad::key_left){
    return true;
  }

  return false;
}

bool transitionS1_6_to_S1_5() {
  if(keypad.getLastReadedKey() == KeyPad::key_up){
    return true;
  }

  return false;
}

bool transitionS1_6_to_S1_7() {
  if(keypad.getLastReadedKey() == KeyPad::key_down){
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


bool transitionS1_7_to_S1_1() {
  if(keypad.getLastReadedKey() == KeyPad::key_down){
    return true;
  }

  return false;
}

bool transitionS1_7_to_S1_6() {
  if(keypad.getLastReadedKey() == KeyPad::key_up){
    return true;
  }

  return false;
}

bool transitionS1_7_to_S1() {
  if(keypad.getLastReadedKey() == KeyPad::key_enter){
    return true;
  }

  return false;
}
#endif // __FILE_STATES_H__