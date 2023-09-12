//------------------------------------------------------------------------------
//
//  Description: This file contains all of the functions relating to what happens
//  when you press either of the switches
//
//  Justin Dhillion
//  March 31 2023
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"



int debouncing1;
int debouncing2;
unsigned int debounce_count1;
unsigned int debounce_count2;
extern int timer_count;
extern volatile unsigned char display_changed;
extern char display_line[4][11];
extern char *display[4];





#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
// Switch 1
  if (P4IFG & SW1) {
       P4IFG &= ~SW1;      //IFG SW1 cleared
       P4IE &= ~SW1;       //Disable switch
       P2IFG &= ~SW2;      //IFG SW1 cleared
       P2IE &= ~SW2;       //Disable switch
    debouncing1=TRUE;
    TB0CCR1 += TB0CCR1_INTERVAL;
    debounce_count1=0;      //Reset debounce counter
    TB0CCTL1 |= CCIE;       //CCR1 enable 
  }
}

#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
// Switch 2
  if (P2IFG & SW2) {
      P2IFG &= ~SW2; // IFG SW1 cleared
       P2IE &= ~SW2; //Disable switch
      P4IFG &= ~SW1; // IFG SW1 cleared
       P4IE &= ~SW1; //Disable switch
     Clear_Display();
     debouncing2 = TRUE; //flag for debouncing
      TB0CCR2 += TB0CCR2_INTERVAL;
      debounce_count2=0; //reset debounce counter
      TB0CCTL2 |= CCIE; // CCR2 enable interrupt
     
      
  }
}

void Debounce_Switches(void){ 
  if(debounce_count1>=4){
      debouncing1=FALSE;
      P4IFG &= ~SW1; // IFG SW1 cleared
      P4IE |= SW1;
      P2IE |= SW2;
       timer_count=RESET;
       debounce_count1=RESET;
       TB0CCTL1 &= ~CCIE;
       
    }
    if(debounce_count2>=4){
      debouncing2=FALSE;
      P2IFG &= ~SW2; // IFG SW2 cleared
      P2IE |= SW2;
      P4IE |= SW1;
      timer_count=RESET;
      debounce_count2=RESET;
      TB0CCTL2 &= ~CCIE;
    }
  
}
