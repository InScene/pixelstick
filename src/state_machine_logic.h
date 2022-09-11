/*
  Copyright Christian Mertens 2022
*/
#ifndef __STATE_MACHINE_LOGIC_H__
#define __STATE_MACHINE_LOGIC_H__

#include "global.h"
#include "states_main_menu.h"
#include "states_file.h"

State* s1 = machine.addState(&s1_file);
State* s1_1 = machine.addState(&s1_1_file_select);
State* s1_1_1 = machine.addState(&s1_1_1_now_playing);
State* s1_1_2 = machine.addState(&s1_1_2_next_file);
State* s1_1_3 = machine.addState(&s1_1_3_prev_file);
State* s1_2 = machine.addState(&s1_2_brightness);
State* s1_2_1 = machine.addState(&s1_2_1_brightness_inc);
State* s1_2_2 = machine.addState(&s1_2_2_brightness_dec);
State* s1_3 = machine.addState(&s1_3_init_delay);
State* s1_3_1 = machine.addState(&s1_3_1_init_delay_inc);
State* s1_3_2 = machine.addState(&s1_3_2_init_delay_dec);
State* s1_4 = machine.addState(&s1_4_frame_delay);
State* s1_4_1 = machine.addState(&s1_4_1_frame_delay_inc);
State* s1_4_2 = machine.addState(&s1_4_2_frame_delay_dec);
State* s1_5 = machine.addState(&s1_5_repeat_times);
State* s1_5_1 = machine.addState(&s1_5_1_repeat_times_inc);
State* s1_5_2 = machine.addState(&s1_5_2_repeat_times_dec);
State* s1_6 = machine.addState(&s1_6_repeat_delay);
State* s1_6_1 = machine.addState(&s1_6_1_repeat_delay_inc);
State* s1_6_2 = machine.addState(&s1_6_2_repeat_delay_dec);
State* s1_7 = machine.addState(&s1_7_main_menu);

void state_machine_setup() {
  /* Add transitions */
  s1->addTransition(&transitionS1_to_S1_1, s1_1);  
  s1_1->addTransition(&transitionS1_1_to_S1, s1);
  s1_1->addTransition(&transitionS1_1_to_S1_1_1, s1_1_1);
  s1_1->addTransition(&transitionS1_1_to_S1_1_2, s1_1_2);
  s1_1->addTransition(&transitionS1_1_to_S1_1_3, s1_1_3);
  s1_1->addTransition(&transitionS1_1_to_S1_2, s1_2);
  s1_1->addTransition(&transitionS1_1_to_S1_7, s1_7);

  s1_1_1->addTransition(&transitionS1_1_1_to_S1_1, s1_1);

  s1_1_2->addTransition(&transitionS1_1_2_to_S1_1, s1_1);
  
  s1_1_3->addTransition(&transitionS1_1_3_to_S1_1, s1_1);

  s1_2->addTransition(&transitionS1_2_to_S1_2_1, s1_2_1);
  s1_2->addTransition(&transitionS1_2_to_S1_2_2, s1_2_2);
  s1_2->addTransition(&transitionS1_2_to_S1_1, s1_1);
  s1_2->addTransition(&transitionS1_2_to_S1_3, s1_3);

  s1_2_1->addTransition(&transitionS1_2_1_to_S1_2, s1_2);

  s1_2_2->addTransition(&transitionS1_2_2_to_S1_2, s1_2);

  s1_3->addTransition(&transitionS1_3_to_S1_3_1, s1_3_1);
  s1_3->addTransition(&transitionS1_3_to_S1_3_2, s1_3_2);
  s1_3->addTransition(&transitionS1_3_to_S1_2, s1_2);
  s1_3->addTransition(&transitionS1_3_to_S1_4, s1_4);

  s1_3_1->addTransition(&transitionS1_3_1_to_S1_3, s1_3);

  s1_3_2->addTransition(&transitionS1_3_2_to_S1_3, s1_3);
  
  s1_4->addTransition(&transitionS1_4_to_S1_4_1, s1_4_1);
  s1_4->addTransition(&transitionS1_4_to_S1_4_2, s1_4_2);
  s1_4->addTransition(&transitionS1_4_to_S1_3, s1_3);
  s1_4->addTransition(&transitionS1_4_to_S1_5, s1_5);

  s1_4_1->addTransition(&transitionS1_4_1_to_S1_4, s1_4);

  s1_4_2->addTransition(&transitionS1_4_2_to_S1_4, s1_4);

  s1_5->addTransition(&transitionS1_5_to_S1_5_1, s1_5_1);
  s1_5->addTransition(&transitionS1_5_to_S1_5_2, s1_5_2);
  s1_5->addTransition(&transitionS1_5_to_S1_4, s1_4);
  s1_5->addTransition(&transitionS1_5_to_S1_6, s1_6);

  s1_5_1->addTransition(&transitionS1_5_1_to_S1_5, s1_5);

  s1_5_2->addTransition(&transitionS1_5_2_to_S1_5, s1_5);

  s1_6->addTransition(&transitionS1_6_to_S1_6_1, s1_6_1);
  s1_6->addTransition(&transitionS1_6_to_S1_6_2, s1_6_2);
  s1_6->addTransition(&transitionS1_6_to_S1_5, s1_5);
  s1_6->addTransition(&transitionS1_6_to_S1_7, s1_7);

  s1_6_1->addTransition(&transitionS1_6_1_to_S1_6, s1_6);

  s1_6_2->addTransition(&transitionS1_6_2_to_S1_6, s1_6);

  s1_7->addTransition(&transitionS1_7_to_S1_1, s1_1);
  s1_7->addTransition(&transitionS1_7_to_S1_6, s1_6);
  s1_7->addTransition(&transitionS1_7_to_S1, s1);
}

#endif // __STATE_MACHINE_LOGIC_H__