/*
  Copyright Christian Mertens 2022
*/
#ifndef __STATES_MAIN_MENU_H__
#define __STATES_MAIN_MENU_H__

#include "global.h"

void S1_file() {
  if(machine.executeOnce){
    #ifdef STATE_DEBUG
      Serial.println("State S1_file");
    #endif
    display.Set(kMenuHeader, kMenuMainHeader, kMenuMainFile);
  }
}

/**
 * Transition from state S1_file to S1_1_FileSelect.
 */
bool TransitionS1_to_S1_1() {
  if(keypad.GetLastReadedKey() == KeyPad::kEnter){
    return true;
  }

  return false;
}

#endif // __STATES_MAIN_MENU_H__