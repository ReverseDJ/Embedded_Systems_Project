#include "functions.h"
#include "macros.h"
#include  "msp430.h"
//------------------------------------------------------------------------------
//
//  Description: This file contains all the port initialization functions
//
//
//  Justin Dhillion
//  February 2023
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------


void Init_Ports(){ //function calls all function initializatioj
	Init_Port_1(); //This function will initialize all pins in port 1.
	Init_Port_2(); //This function will initialize all pins in port 2.
	Init_Port_3(); //This function will initialize all pins in port 3.
	Init_Port_4(); //This function will initialize all pins in port 4.
	Init_Port_5(); //This function will initialize all pins in port 5.
	Init_Port_6(); //This function will initialize all pins in port 6.
}

void Init_Port_1(void){
//-------------------------------------------------------
//Configure Port 1
// Port 1 Pins
// RED_LED (0x01) // 0 RED LED 0
// V_A1_SEEED (0x02) // 1 A1_SEEED
// V_DETECT_L (0x04) // 2 V_DETECT_L
// V_DETECT_R (0x08) // 3 V_DETECT_R
// V_A4_SEEED (0x10) // 4 V_A4_SEEED
// V_THUMB (0x20) // 5 V_THUMB
// UCA0RXD (0x40) // 6 Back Channel UCA0RXD
// UCA0TXD (0x80) // 7 Back Channel UCA0TXD
//-------------------------------------------------------
P1DIR = 0x00; // Set P1 direction to input
P1OUT = 0x00; // P1 set Low

//Port 1 Pin 0 
P1SEL0 &= ~RED_LED; // Set RED_LED as GP I/O
P1SEL1 &= ~RED_LED; // Set RED_LED as GP I/O
P1OUT |= RED_LED; // Set Red LED On
P1DIR |= RED_LED; // Set Red LED direction to output

//Port 1 Pin 1
P1SELC |= V_A1_SEEED; // ADC input for A1_SEEED

//Port 1 Pin 2
P1SELC |= V_DETECT_L; // ADC input for V_DETECT_L

//Port 1 Pin 3
P1SELC |= V_DETECT_R; // ADC input for V_DETECT_R

//Port 1 Pin 4
P1SELC |= V_A4_SEEED; // ADC input for V_A4_SEEED

//Port 1 Pin 5
P1SELC |= V_THUMB; // ADC input for V_THUMB

//Port 1 Pin 6
P1SEL0 |= UCA0TXD; // UCA0TXD pin
P1SEL1 &= ~UCA0TXD; // UCA0TXD pin

//Port 1 Pin 7
P1SEL0 |= UCA0RXD; // UCA0RXD pin
P1SEL1 &= ~UCA0RXD; // UCA0RXD pin
//-------------------------------------------------------
}

void Init_Port_2(){ // Configure Port 2

P2OUT = 0x00; // P2 set Low
P2DIR = 0x00; // Set P2 direction to output

//P2 Pin 0
P2SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
P2SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
P2OUT &= ~RESET_LCD; // Initial Value = Low / Off
P2DIR |= RESET_LCD; // Direction = output

//P2 Pin 1

P2SEL0 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
P2SEL1 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
P2OUT &= ~CHECK_BAT; // Initial Value = Low / Off
P2DIR |= CHECK_BAT; // Direction = output

//P2 Pin 2

P2SEL0 &= ~IR_LED; // P2_2 GPIO operation
P2SEL1 &= ~IR_LED; // P2_2 GPIO operation
P2OUT &= ~IR_LED; // Initial Value = Low / Off
P2DIR &= ~IR_LED; // Direction = input for now

//P2 Pin 3

P2SEL0 &= ~SW2; // SW2 set as I/0
P2SEL1 &= ~SW2; // SW2 set as I/0
P2DIR &= ~SW2; // SW2 Direction = input
P2PUPD |= SW2; // Configure pull-up resistor SW2
P2REN |= SW2; // Enable pull-up resistor SW2
P2IES |= SW2; // SW2 Hi/Lo edge interrupt (Falling edge)
P2IFG &= ~SW2; // IFG SW1 cleared
P2IE |= SW2; // SW1 interrupt Enabled

//P2 Pin 4

P2SEL0 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
P2SEL1 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
P2OUT &= ~IOT_RUN_RED; // Initial Value = Low / Off
P2DIR |= IOT_RUN_RED; // Direction = input

//P2 Pin 5

P2SEL0 &= ~DAC_ENB; // DAC_ENB GPIO operation
P2SEL1 &= ~DAC_ENB; // DAC_ENB GPIO operation
P2OUT |= DAC_ENB; // Initial Value = High
P2DIR |= DAC_ENB; // Direction = output

//P2 Pin 6

P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
P2SEL1 |= LFXOUT; // LFXOUT Clock operation

//P2 Pin7

P2SEL0 &= ~LFXIN; // LFXIN Clock operation
P2SEL1 |= LFXIN; // LFXIN Clock operation
//------------------------------------------------------------------------------
}

void Init_Port_3(){
P3OUT = 0x00; // P3 set Low
P3DIR = 0x00; // Set P3 direction to output
// P3 PIN 0

P3SEL0 &= ~TEST_PROBE;  //GPIO
P3SEL1 &= ~TEST_PROBE;
P3OUT &= ~TEST_PROBE;
P3DIR |= TEST_PROBE;

// P3 PIN 1

P3SEL0 &= ~OA2O; // OA2O GPIO operation
P3SEL1 &= ~OA2O; // OA2O GPIO operation
P3OUT &= ~OA2O; // Set OA2O OFF [Low]
P3DIR |= OA2O; // Set direction to output

// P3 PIN 2

P3SEL0 &= ~OA2N;
P3SEL1 &= ~OA2N;
P3OUT &= ~OA2N;
P3DIR |= OA2N;

// P3 PIN 3

P3SEL0 &= ~OA2P;
P3SEL1 &= ~OA2P;
P3OUT &= ~OA2P;
P3DIR |= OA2P;

// P3 PIN 4

P3SEL1 &= ~SMCLK; // SMCLK GPIO operation
P3SEL0 &= ~SMCLK; // SMCLK GPIO operation
P3OUT &= ~SMCLK; // Set SMCLK OFF [Low]
P3DIR |= SMCLK; // Set direction to output;

// P3 PIN 5

P3SEL0 &= ~DAC_CNTL;
P3SEL1 &= ~DAC_CNTL;
P3OUT &= ~DAC_CNTL;
P3DIR &= ~DAC_CNTL;

// P3 PIN 6

P3SEL0 &= ~IOT_LINK_GRN;
P3SEL1 &= ~IOT_LINK_GRN;
P3OUT &= ~IOT_LINK_GRN;
P3DIR |= IOT_LINK_GRN;

// P3 PIN 7

P3SEL0 &= ~IOT_EN;
P3SEL1 &= ~IOT_EN;
P3OUT &= ~IOT_EN;
P3DIR |= IOT_EN;


}

void Init_Port_4(){
P4OUT = 0x00; // P5 set Low
P4DIR = 0x00; // Set P5 direction to output

// P4 PIN 0

P4SEL0 &= ~DAC_CNTL1; // DAC_CNTL1 GPIO operation
P4SEL1 &= ~DAC_CNTL1; // DAC_CNTL1 GPIO operation
P4DIR &= ~DAC_CNTL1; // Set P4_0 direction to input

// P4 PIN 1

P4SEL0 &= ~SW1; // SW1 set as I/0
P4SEL1 &= ~SW1; // SW1 set as I/0
 P4DIR &= ~SW1; // SW1 Direction = input
P4PUPD |= SW1; // Configure pull-up resistor SW1
 P4REN |= SW1; // Enable pull-up resistor SW1
 P4IES |= SW1; // SW1 Hi/Lo edge interrupt
 P4IFG &= ~SW1; // IFG SW1 cleared
  P4IE |= SW1; // SW1 interrupt Enabled

// P4 PIN 2

P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation

// P4 PIN 3

P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation

// P4 PIN 4

P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output

// P4 PIN 5

P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation

// P4 PIN 6

P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation

// P4 PIN 7

P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
//--------------------------------------------------------------------
}

void Init_Port_5(void){
//--------------------------------------------------------
// Port 5 Pins
// V_BAT (0x01) // 0 V_BAT
// V_5_0 (0x02) // 1 V_5_0
// V_DAC (0x04) // 2 V_DAC
// V_3_3 (0x08) // 3 V_3.3
// IOT_PROG_MODE (0x10) // 4 IOT_PROGRAM_MODE
//--------------------------------------------------------
P5DIR = 0x00; // Set P1 direction to input
P5OUT = 0x00; // P1 set Low

// P5 PIN 0
P5SELC |= V_BAT; // ADC input for V_BAT

// P5 PIN 1
P5SELC |= V_5_0; // ADC input for V_BAT

// P5 PIN 2
P5SELC |= V_DAC; // ADC input for V_DAC

// P5 PIN 3
P5SELC |= V_3_3; // ADC input for V_3_3

// P5 PIN 4
P5SEL0 &= ~IOT_BOOT; // IOT_BOOT GPIO operation
P5SEL1 &= ~IOT_BOOT; // IOT_BOOT GPIO operation
P5OUT |= IOT_BOOT; // Set Output value inactive
P5DIR |= IOT_BOOT; // Set direction to output
//------------------------------------------------------
}

void Init_Port_6(){
//P6 Pin 0
P6SEL0 |= LCD_BACKLITE;
P6SEL1 &= ~LCD_BACKLITE;

P6DIR |= LCD_BACKLITE;

//P6 Pin 1

P6SEL0 |= R_FORWARD;
P6SEL1 &= ~R_FORWARD;

P6DIR |= R_FORWARD;

//P6 Pin 2

P6SEL0 |= R_REVERSE;
P6SEL1 &= ~R_REVERSE;

P6DIR |= R_REVERSE;

//P6 Pin 3

P6SEL0 |= L_FORWARD;
P6SEL1 &= ~L_FORWARD;

P6DIR |= L_FORWARD;

//P6 Pin 4

P6SEL0 |= L_REVERSE;
P6SEL1 &= ~L_REVERSE;

P6DIR |= L_REVERSE;

//P6 Pin 5

P6SEL0 &= ~P6_5;
P6SEL1 &= ~P6_5;
P6OUT &= ~P6_5;
P6DIR &= ~P6_5;

//P6 Pin 6

P6SEL0 &= ~GRN_LED;
P6SEL1 &= ~GRN_LED;
P6OUT &= ~GRN_LED;
P6DIR |= GRN_LED;

}