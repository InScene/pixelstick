/*
  Copyright Christian Mertens 2022
*/
#ifndef __STATES_MAIN_MENU_H__
#define __STATES_MAIN_MENU_H__

#include "global.h"

void s1_file() {
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State s1_file");
    #endif
    display.Set(kMenuHeader, kMenuMainHeader, kMenuMainFile);
  }
}

/**
 * Transition from state s1_file to s1_1_file_select.
 */
bool transitionS1_to_S1_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kEnter){
    return true;
  }

  return false;
}

#endif // __STATES_MAIN_MENU_H__