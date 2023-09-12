//------------------------------------------------------------------------------
//
//  Description: This file contains functions relating to finding and navigating the black circle
//
//
//  Justin Dhillion
//  March 1 2023
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

extern int wheel_count;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern char display_line[4][11];
extern volatile unsigned char display_changed;
int detect_diff;
extern int circle_count;
extern int line_status;



void Find_Line(){
  if ((line_status==START)&&(wheel_count==STARTFIND)){ 
     strcpy(display_line[2], " FINDING ");
     display_changed = TRUE;
     line_arc();
     line_status=FINDING;
      
  }
   else if(((ADC_Right_Detect>=BLVALUE) || (ADC_Left_Detect>=BLVALUE))&&(line_status==FINDING)){
       wheels_off();
       strcpy(display_line[2], "BL FOUND! ");
       display_changed = TRUE;
       line_status=INTERCEPT;
       wheel_count=RESET;
   }
   else if((wheel_count==STARTTURN) && (line_status==INTERCEPT)){
      wheels_counterclockwise_slow();
      strcpy(display_line[2], " TURNING! ");
      display_changed = TRUE;
      line_status=TURNING;
      wheel_count=RESET;
   }
   else if((wheel_count==15) && (line_status==TURNING)){
      wheels_off();
      strcpy(display_line[2], "BL TURNED!");
      display_changed = TRUE;
      line_status=LINE;
      wheel_count=RESET;
   }
}

void Navigate_Line(){
  detect_diff=ADC_Left_Detect-ADC_Right_Detect;
    if(line_status==LINE || line_status==CIRCLE){
      if((ADC_Left_Detect>=GRAYL && ADC_Right_Detect>=GRAYR)||(ADC_Left_Detect>=BLVALUE || ADC_Right_Detect>=BLVALUE))
        wheels_forward_slow();
      else if(detect_diff+OFFSET<0)
        right_turn_sharp();
      else if(detect_diff-OFFSET>0)
        left_turn_sharp();
    }
    if(wheel_count==STARTTRAVEL && line_status==LINE){
      wheels_off();
      strcpy(display_line[2], "BL TRAVEL!");
      display_changed=TRUE;
      line_status=PAUSE;
      wheel_count=RESET;
    }
    if(wheel_count==STARTCIRCLE && line_status==PAUSE){
      line_status=CIRCLE;
      wheel_count=RESET;
    }
}
