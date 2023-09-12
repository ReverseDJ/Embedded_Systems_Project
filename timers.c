//------------------------------------------------------------------------------
//
//  Description: This file contains the timer functions and interupts
//
//
//  Justin Dhillion
//  March 1 2023
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------


//--------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"
int timer_count;
int cirlce_timer;
int display_count;
extern unsigned int debounce_count1;
extern unsigned int debounce_count2;
extern int debouncing1;
extern int debouncing2;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern int wheel_status;
int wheel_count;
extern volatile unsigned char PC_2_IOT[RING_SIZE];
extern int command_done;
extern int A0_position;
int command_counter;
extern int line_status;


void Init_Timers(){
  Init_Timer_B0();
  Init_Timer_B1();
  Init_Timer_B3();
}

// Timer B0 initialization sets up both B0_0, B0_1-B0_2 and overflow
void Init_Timer_B0(void) {
   TB0CTL = TBSSEL__SMCLK; // SMCLK source
  TB0CTL |= TBCLR; // Resets TB0R,
  TB0CTL |= MC__CONTINOUS; // Continuous up to 0xFFFF and overflow
  TB0CTL |= ID__8; // Divide clock by 8
  
   TB0EX0 = TBIDEX__8; // Divide clock by an additional 8
   
 
    TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
    TB0CCTL0 |= CCIE; // CCR0 enable interrupt
 
 
}
//--------------------------------------------------------------------

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//----------------------------------------------------------------------------
  
  TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
  timer_count++;
  
  if (display_count==REFRESH){
    update_display=TRUE;
    display_count=RESET;
    }
  else
    display_count++;
  
  if(timer_count>=HUNDEREDMS){
    P3OUT |= IOT_EN;
  }
}
  
  


//----------------------------------------------------------------------------

    
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB0IV,14)){
case 0: 
  break; // No interrupt
case 2: // CCR1 not used
   TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
     debounce_count1++;
     
     P4IFG &= ~SW1; // IFG SW1 cleared
     P2IFG &= ~SW2; // IFG SW1 cleared

  break;
case 4: // CCR2 not used
   TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
     debounce_count2++;
     
     P4IFG &= ~SW1; // IFG SW1 cleared
     P2IFG &= ~SW2; // IFG SW1 cleared

  break;
case 14: // overflow
  break;
default: break;
}
//----------------------------------------------------------------------------
}


// Timer B1 initialization sets up both B1_0, B1_1-B1_2 and overflow
void Init_Timer_B1(void) {
   TB1CTL = TBSSEL__SMCLK; // SMCLK source
  TB1CTL |= TBCLR; // Resets TB1R,
  TB1CTL |= MC__CONTINOUS; // Continuous up to 0xFFFF and overflow
  TB1CTL |= ID__8; // Divide clock by 8
  
   TB1EX0 = TBIDEX__8; // Divide clock by an additional 8
   
 
    TB1CCR0 = TB1CCR0_INTERVAL; // CCR0
    TB1CCTL0 &= ~CCIE; // CCR0 enable interrupt
  
  TB1CTL &= ~TBIE; // Disable Overflow Interrupt
  TB1CTL &= ~TBIFG; // Clear Overflow Interrupt flag
  
  
}
//--------------------------------------------------------------------

#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB1 0 Interrupt handler
//----------------------------------------------------------------------------
  
  TB1CCR0 += TB1CCR0_INTERVAL; // Add Offset to TB1CCR0
  ADCCTL0 |= ADCENC; // Enable Conversions
  ADCCTL0 |= ADCSC;
  
  if (line_status){
    wheel_count++;
  }
 
}

#pragma vector=TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB1 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB1IV,14)){
case 0: 
  break; // No interrupt
case 2: // CCR1 not used
   TB1CCR1 += TB1CCR1_INTERVAL; // Add Offset to TBCCR1
   command_counter++;
   if (command_counter==12 && command_done==DONE){
      strcpy((char*)PC_2_IOT,PING);
      UCA0IE |= UCTXIE;
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
      command_counter=RESET;
    }
   
     
  break;
case 4: // CCR2 not used
   TB1CCR2 += TB1CCR2_INTERVAL; // Add Offset to TBCCR2
     

  break;
case 14: // overflow
  break;
default: break;
}
//----------------------------------------------------------------------------
}
    
//----------------------------------------------------------------------------

void Init_Timer_B3(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TB3.1 P6.0 LCD_BACKLITE
// TB3.2 P6.1 L_FORWARD
// TB3.3 P6.2 L_REVERSE
// TB3.4 P6.3 R_FORWARD
// TB3.5 P6.4 R_REVERSE
//------------------------------------------------------------------------------
        TB3CTL = TBSSEL__SMCLK; // SMCLK
       TB3CTL |= MC__UP; // Up Mode
       TB3CTL |= TBCLR; // Clear TAR
       
    PWM_PERIOD = 50005; // PWM Period [Set this to 50005]
    
    TB3CCTL1 = OUTMOD_7; // CCR1 reset/set
    LCD_BACKLITE_DIMING = PERCENT_50; // P6.0 Right Forward PWM duty cycle
    
    TB3CCTL2 = OUTMOD_7; // CCR2 reset/set
    LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Right Forward PWM duty cycle
    
    TB3CCTL3 = OUTMOD_7; // CCR3 reset/set
    LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
    
    TB3CCTL4 = OUTMOD_7; // CCR4 reset/set
    RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.3 Left Forward PWM duty cycle
    
    TB3CCTL5 = OUTMOD_7; // CCR5 reset/set
    RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.4 Left Reverse PWM duty cycle
    
    
    
//------------------------------------------------------------------------------
}

