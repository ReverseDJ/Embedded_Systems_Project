#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

char state;
int count_debounce_SW1;
int okay_to_look_at_switch1;
int sw1_position;
int delay_start;
int right_motor_count,left_motor_count;
int segment_count;
int turn_count;


void Switches_Process(){
  if (okay_to_look_at_switch1 && sw1_position){
    if (!(P4IN & SW1)){
      sw1_position = PRESSED;
      okay_to_look_at_switch1 = NOT_OKAY;
      count_debounce_SW1 = DEBOUNCE_RESTART;
      if (change==7){
        change=1;
      }
      else{
        change++;
      }
      state=PAUSE;
    }
  }
    if (count_debounce_SW1 <= DEBOUNCE_TIME){
      count_debounce_SW1++;
  }       
  else{
    okay_to_look_at_switch1 = OKAY;
      if (P4IN & SW1){
        sw1_position = RELEASED;
     }
  }
}

//Cases for state machine

void pause_case(){
  if(time_change){
    time_change = 0;
    if(delay_start++ >= WAITING2START){
      delay_start = 0;
      state = GO;
    }
  }
}
void go_case(){
 cycle_time = 0;
 right_motor_count = 0;
 left_motor_count = 0;
 //wheels_forward();
 segment_count = 0;
 state = RUN;
}

void end_case(){
 wheels_off();
 //state = PAUSE;
 //change = NONE;
}

void Run_Triangle1(void){
  
 strcpy(display_line[0], "          ");
 strcpy(display_line[1], " Triangle ");
 strcpy(display_line[2], "          ");
 strcpy(display_line[3], "          ");
 display_changed = TRUE;
 
 switch(state){
 case PAUSE:
   pause_case();
   break;
 case GO: // Begin
   go_case();
   break; //
 case RUN: // Run
   if(time_change){
     time_change = 0;
     if((segment_count <= TRAVEL_DISTANCE_TS)){
       if(right_motor_count++ >= RIGHT_COUNT_TIME_TS){
         P6OUT &= ~R_FORWARD;
       }
       if(left_motor_count++ >= LEFT_COUNT_TIME_TS){
         P6OUT &= ~L_FORWARD;
       }
       if(cycle_time >= WHEEL_COUNT_TIME){
          cycle_time = 0;
          right_motor_count = 0;
          left_motor_count = 0;
          segment_count++;
          wheels_forward();
       }
     }
     else{
       state = GO;
       change++;
     }
 }
   break;
 case END: // End
   end_case();
   break; //
 default: 
   state=PAUSE;
   break;
 }
}
 void Run_Triangle2(){
   strcpy(display_line[0], "          ");
   strcpy(display_line[1], " Triangle ");
   strcpy(display_line[2], "          ");
   strcpy(display_line[3], "          ");
   display_changed = TRUE;
   
 switch(state){
 case PAUSE:
   pause_case();
   break;
 case GO: // Begin
   go_case();
   break; //
 case RUN: // Run
   if(time_change){
     time_change = 0;
     if(segment_count <= TRAVEL_DISTANCE_TT){
       if(right_motor_count++ >= RIGHT_COUNT_TIME_TT){
         P6OUT &= ~R_FORWARD;
       }
       if(left_motor_count++ >= LEFT_COUNT_TIME_TT){
         P6OUT &= ~L_FORWARD;
       }
       if(cycle_time >= WHEEL_COUNT_TIME){
          cycle_time = 0;
          right_motor_count = 0;
          left_motor_count = 0;
          segment_count++;
          //wheels_forward();
          P6OUT |= R_FORWARD; // Set Port pin High [Wheel On]
       }
     }

     else{
       if(turn_count <=4){
         state=GO;
         change--;
         turn_count++;
       }
       else{
         state = END;
       }
     }
 }
 break; //
 case END: // End
  end_case();
  break; //
 default: 
   state=PAUSE;
   break;
 }
   
 }

void Run_Circle(void){
   strcpy(display_line[0], "          ");
   strcpy(display_line[1], "  Circle  ");
   strcpy(display_line[2], "          ");
   strcpy(display_line[3], "          ");
  display_changed = TRUE;
  
  switch(state){
 case PAUSE:
   pause_case();
   break;
 case GO: // Begin
   go_case();
   break; //
 case RUN: // Run
   if(time_change){
     time_change = 0;
     if(segment_count <= TRAVEL_DISTANCE_C){
       if(right_motor_count++ >= RIGHT_COUNT_TIME_C){
         P6OUT &= ~R_FORWARD;
       }
       if(left_motor_count++ >= LEFT_COUNT_TIME_C){
         P6OUT &= ~L_FORWARD;
       }
       if(cycle_time >= WHEEL_COUNT_TIME){
          cycle_time = 0;
          right_motor_count = 0;
          left_motor_count = 0;
          segment_count++;
          wheels_forward();
       }
     }
     else{
       state = END;
     }
 }
    break; //
 case END: // End
   end_case();
  return; //
 default: 
   state=PAUSE;
   break;
 }
}
void Run_Figure1(void){
   strcpy(display_line[0], "          ");
   strcpy(display_line[1], " Figure 8 ");
   strcpy(display_line[2], "          ");
   strcpy(display_line[3], "          ");
   display_changed = TRUE;
   
 switch(state){
 case PAUSE:
   pause_case();
   break;
 case GO: // Begin
   go_case();
   break; //
 case RUN: // Run
   if(time_change){
     time_change = 0;
     if((segment_count <= TRAVEL_DISTANCE_FC)){
       if(right_motor_count++ >= RIGHT_COUNT_TIME_FC){
         P6OUT &= ~R_FORWARD;
       }
       if(left_motor_count++ >= LEFT_COUNT_TIME_FC){
         P6OUT &= ~L_FORWARD;
       }
       if(cycle_time >= WHEEL_COUNT_TIME){
          cycle_time = 0;
          right_motor_count = 0;
          left_motor_count = 0;
          segment_count++;
          wheels_forward();
       }
     }
     else{
       state = GO;
       change++;
     }
 }
    break; //
 case END: // End
  break;
 default: 
   state=PAUSE;
   break;
 }
}

void Run_Figure2(void){
   strcpy(display_line[0], "          ");
   strcpy(display_line[1], " Figure 8 ");
   strcpy(display_line[2], "          ");
   strcpy(display_line[3], "          ");
   display_changed = TRUE;
   
 switch(state){
 case PAUSE:
   pause_case();
   break;
 case GO: // Begin
   go_case();
   break; //
 case RUN: // Run
   if(time_change){
     time_change = 0;
     if((segment_count <= TRAVEL_DISTANCE_FCC)){
       if(right_motor_count++ >= RIGHT_COUNT_TIME_FCC){
         P6OUT &= ~R_FORWARD;
       }
       if(left_motor_count++ >= LEFT_COUNT_TIME_FCC){
         P6OUT &= ~L_FORWARD;
       }
       if(cycle_time >= WHEEL_COUNT_TIME){
          cycle_time = 0;
          right_motor_count = 0;
          left_motor_count = 0;
          segment_count++;
          wheels_forward();
       }
     }
     else{
       state = GO;
       change++;
     }
 }
 break; //
 case END: // End
  end_case();
  break; //
 default: 
   state=PAUSE;
   break;
 }
}
void Run_Figure_end(){
  strcpy(display_line[0], "          ");
   strcpy(display_line[1], " Figure 8 ");
   strcpy(display_line[2], "          ");
   strcpy(display_line[3], "          ");
  display_changed = TRUE;
  
  switch(state){
 case PAUSE:
   pause_case();
   break;
 case GO: // Begin
   go_case();
   break; //
 case RUN: // Run
   if(time_change){
     time_change = 0;
     if(segment_count <= TRAVEL_DISTANCE_FCC){
       if(right_motor_count++ >= RIGHT_COUNT_TIME_FCC){
         P6OUT &= ~R_FORWARD;
       }
       if(left_motor_count++ >= LEFT_COUNT_TIME_FCC){
         P6OUT &= ~L_FORWARD;
       }
       if(cycle_time >= WHEEL_COUNT_TIME){
          cycle_time = 0;
          right_motor_count = 0;
          left_motor_count = 0;
          segment_count++;
          wheels_forward();
       }
     }
     else{
       state = END;
     }
 }
    break; //
 case END: // End
   end_case();
  return; //
 default: 
   state=PAUSE;
   break;
 }
}
