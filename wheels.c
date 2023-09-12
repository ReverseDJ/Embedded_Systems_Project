//------------------------------------------------------------------------------
//
//  Description: This file contains all functions controlling the wheels
//
//
//  Justin Dhillion
//  February 2023
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include "functions.h"
#include "macros.h"
#include  "msp430.h"

//Wheels off
void wheels_off(){
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
}

//Wheels Forward Fast
void wheels_forward_fast(){
  LEFT_FORWARD_SPEED = FAST_LEFT;
  RIGHT_FORWARD_SPEED = FAST_RIGHT;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
}

void wheels_forward_slow(){
  LEFT_FORWARD_SPEED = SLOW_LEFT;
  RIGHT_FORWARD_SPEED = SLOW_RIGHT;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
}
//Wheels Reverse 
 void wheels_reverse(){
  LEFT_REVERSE_SPEED = FAST_LEFT;
  RIGHT_REVERSE_SPEED = FAST_RIGHT;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
}

 void wheels_reverse_slow(){
  LEFT_REVERSE_SPEED = SLOW_LEFT;
  RIGHT_REVERSE_SPEED = SLOW_RIGHT;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
 }

//Turn car clockwise
void wheels_clockwise(){
  RIGHT_REVERSE_SPEED = FAST_RIGHT;
  LEFT_FORWARD_SPEED = FAST_LEFT;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
}

void wheels_clockwise_slow(){
  RIGHT_REVERSE_SPEED = SLOW_RIGHT;
  LEFT_FORWARD_SPEED = SLOW_LEFT;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  RIGHT_FORWARD_SPEED = WHEEL_OFF;

}
//Turn car counterclockwise
void wheels_counterclockwise(){
  RIGHT_FORWARD_SPEED = FAST_RIGHT;
  LEFT_REVERSE_SPEED = FAST_LEFT;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
}

void wheels_counterclockwise_slow(){
  RIGHT_FORWARD_SPEED = SLOW_RIGHT;
  LEFT_REVERSE_SPEED = SLOW_LEFT;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
}

void right_turn_sharp(){
   RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = SLOW_LEFT;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
}

void left_turn_sharp(){
  RIGHT_FORWARD_SPEED = SLOW_RIGHT;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
}

void right_turn(){
   RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = MEDIUM_LEFT;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  RIGHT_FORWARD_SPEED = SLOW_RIGHT;
}

void left_turn(){
  RIGHT_FORWARD_SPEED = MEDIUM_RIGHT;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = SLOW_LEFT;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
}

void line_arc(){
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = ARC_LEFT;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  RIGHT_FORWARD_SPEED = ARC_RIGHT;
}