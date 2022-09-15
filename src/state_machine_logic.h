/*
  Copyright Christian Mertens 2022
*/
#ifndef __STATE_MACHINE_LOGIC_H__
#define __STATE_MACHINE_LOGIC_H__

#include "global.h"
#include "states_main_menu.h"
#include "states_file.h"

State* s1 = machine.addState(&S1_file);
State* s1_1 = machine.addState(&S1_1_FileSelect);
State* s1_1_1 = machine.addState(&S1_1_1_NowPlaying);
State* s1_1_2 = machine.addState(&S1_1_2_NextFile);
State* s1_1_3 = machine.addState(&S1_1_3_PrevFile);
State* s1_2 = machine.addState(&S1_2_Brightness);
State* s1_2_1 = machine.addState(&S1_2_1_BrightnessInc);
State* s1_2_2 = machine.addState(&S1_2_2_BrightnessDec);
State* s1_3 = machine.addState(&S1_3_InitDelay);
State* s1_3_1 = machine.addState(&S1_3_1_InitDelayInc);
State* s1_3_2 = machine.addState(&S1_3_2_InitDelayDec);
State* s1_4 = machine.addState(&S1_4_FrameDelay);
State* s1_4_1 = machine.addState(&S1_4_1_FrameDelayInc);
State* s1_4_2 = machine.addState(&S1_4_2_FrameDelayDec);
State* s1_5 = machine.addState(&S1_5_RepeatTimes);
State* s1_5_1 = machine.addState(&S1_5_1_RepeatTimesInc);
State* s1_5_2 = machine.addState(&S1_5_2_RepeatTimesDec);
State* s1_6 = machine.addState(&S1_6_RepeatDelay);
State* s1_6_1 = machine.addState(&S1_6_1_RepeatDelayInc);
State* s1_6_2 = machine.addState(&S1_6_2_RepeatDelayDec);
State* s1_7 = machine.addState(&S1_7_ResetValues);
State* s1_7_1 = machine.addState(&S1_7_1_ResetToDefault);
State* s1_8 = machine.addState(&S1_8_MainMenu);

void StateMachineSetup() {
  /* Add TransitionS */
  s1->addTransition(&TransitionS1_to_S1_1, s1_1);  
  s1_1->addTransition(&TransitionS1_1_to_S1, s1);
  s1_1->addTransition(&TransitionS1_1_to_S1_1_1, s1_1_1);
  s1_1->addTransition(&TransitionS1_1_to_S1_1_2, s1_1_2);
  s1_1->addTransition(&TransitionS1_1_to_S1_1_3, s1_1_3);
  s1_1->addTransition(&TransitionS1_1_to_S1_2, s1_2);
  s1_1->addTransition(&TransitionS1_1_to_S1_8, s1_8);

  s1_1_1->addTransition(&TransitionS1_1_1_to_S1_1, s1_1);

  s1_1_2->addTransition(&TransitionS1_1_2_to_S1_1, s1_1);
  
  s1_1_3->addTransition(&TransitionS1_1_3_to_S1_1, s1_1);

  s1_2->addTransition(&TransitionS1_2_to_S1_2_1, s1_2_1);
  s1_2->addTransition(&TransitionS1_2_to_S1_2_2, s1_2_2);
  s1_2->addTransition(&TransitionS1_2_to_S1_1, s1_1);
  s1_2->addTransition(&TransitionS1_2_to_S1_3, s1_3);

  s1_2_1->addTransition(&TransitionS1_2_1_to_S1_2, s1_2);

  s1_2_2->addTransition(&TransitionS1_2_2_to_S1_2, s1_2);

  s1_3->addTransition(&TransitionS1_3_to_S1_3_1, s1_3_1);
  s1_3->addTransition(&TransitionS1_3_to_S1_3_2, s1_3_2);
  s1_3->addTransition(&TransitionS1_3_to_S1_2, s1_2);
  s1_3->addTransition(&TransitionS1_3_to_S1_4, s1_4);

  s1_3_1->addTransition(&TransitionS1_3_1_to_S1_3, s1_3);

  s1_3_2->addTransition(&TransitionS1_3_2_to_S1_3, s1_3);
  
  s1_4->addTransition(&TransitionS1_4_to_S1_4_1, s1_4_1);
  s1_4->addTransition(&TransitionS1_4_to_S1_4_2, s1_4_2);
  s1_4->addTransition(&TransitionS1_4_to_S1_3, s1_3);
  s1_4->addTransition(&TransitionS1_4_to_S1_5, s1_5);

  s1_4_1->addTransition(&TransitionS1_4_1_to_S1_4, s1_4);

  s1_4_2->addTransition(&TransitionS1_4_2_to_S1_4, s1_4);

  s1_5->addTransition(&TransitionS1_5_to_S1_5_1, s1_5_1);
  s1_5->addTransition(&TransitionS1_5_to_S1_5_2, s1_5_2);
  s1_5->addTransition(&TransitionS1_5_to_S1_4, s1_4);
  s1_5->addTransition(&TransitionS1_5_to_S1_6, s1_6);

  s1_5_1->addTransition(&TransitionS1_5_1_to_S1_5, s1_5);

  s1_5_2->addTransition(&TransitionS1_5_2_to_S1_5, s1_5);

  s1_6->addTransition(&TransitionS1_6_to_S1_6_1, s1_6_1);
  s1_6->addTransition(&TransitionS1_6_to_S1_6_2, s1_6_2);
  s1_6->addTransition(&TransitionS1_6_to_S1_5, s1_5);
  s1_6->addTransition(&TransitionS1_6_to_S1_7, s1_7);

  s1_6_1->addTransition(&TransitionS1_6_1_to_S1_6, s1_6);

  s1_6_2->addTransition(&TransitionS1_6_2_to_S1_6, s1_6);

  s1_7->addTransition(&TransitionS1_7_to_S1_8, s1_8);
  s1_7->addTransition(&TransitionS1_7_to_S1_6, s1_6);
  s1_7->addTransition(&TransitionS1_7_to_S1_7_1, s1_7_1);

  s1_7_1->addTransition(&TransitionS1_7_1_to_S1_7, s1_7);

  s1_8->addTransition(&TransitionS1_8_to_S1_1, s1_1);
  s1_8->addTransition(&TransitionS1_8_to_S1_7, s1_7);
  s1_8->addTransition(&TransitionS1_8_to_S1, s1);
}

#endif // __STATE_MACHINE_LOGIC_H__