//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Justin Dhillion
//  March 1 2023
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"


  // Global Variables
volatile char slow_input_down;
unsigned char display_mode;
extern int timer_count;
extern unsigned int debounce_count1;
extern unsigned int debounce_count2;
extern int debouncing1;
extern int debouncing2;
extern char display_line[4][11];
extern char *display[4];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
int state;







void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
  PM5CTL0 &= ~LOCKLPM5;
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings

  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions and interuppts
  Init_LCD();                          // Initialize LCD
  Init_Timers();                       // Initialize Timers
  Init_ADC();
  Init_Serial_Ports();
  
  
  

// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
  strcpy(display_line[0], "          ");
  strcpy(display_line[1], "          ");
  strcpy(display_line[2], "          ");
  strcpy(display_line[3], "          ");

// This line identifies the text on the Display is to change.
  display_changed = TRUE;

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    Display_Process();                  // Update Display
    P3OUT ^= TEST_PROBE;// Change State of TEST_PROBE OFF
    Debounce_Switches();  
    IOT_Process();
    Find_Line();
    Navigate_Line();
    if (state==BOOTUP){
      IOT_BOOTUP();
    }
  }
    
    
    
    


//------------------------------------------------------------------------------
}

