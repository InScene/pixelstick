/*
  Copyright Christian Mertens 2022
*/
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <StateMachine.h>
#include "display.h"
#include "keypad.h"
#include "logic_values.h"
#include "strip_handler.h"
#include "file_handler.h"

Display display = Display();
KeyPad keypad = KeyPad();
LogicValues logicValues = LogicValues();
StripHandler stripHandler = StripHandler();
FileHandler filehandler = FileHandler(stripHandler);

//#define STATE_DEBUG 1
StateMachine machine = StateMachine();

#endif // __GLOBAL_H__