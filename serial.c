//------------------------------------------------------------------------------
//
//  Description: This file contains the serial communications functions and interrupts
//
//
//  Justin Dhillion
//  March 31 2023
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"

char pb_index; // Index for process_buffer

// Serial
volatile unsigned char IOT_2_PC[RING_SIZE];
volatile unsigned int iot_rx_wr;
unsigned int iot_rx_rd; // Only used in Main
unsigned int direct_iot; // Only used it Interrupt

volatile unsigned char PC_2_IOT[RING_SIZE];
volatile unsigned int usb_rx_wr;
unsigned int usb_rx_rd; // Only used in Main
unsigned int direct_usb; // Only used it Interrupt

char A1_Process_Buffer[64];
char A0_Process_Buffer[64];
char bootup[32];
extern int button_pressed;
extern char display_line[4][11];
extern volatile unsigned char display_changed;
int cleared;
int A0_position;
int A1_position;
int line;
int command;
int boot_state;
char * token;
char * ipstr1;
char * ipstr2;
char * dot2;
char * end;
int size;
int command_done;
extern int state;
extern int command_counter;
int arrive_counter;
int line_status;
extern int wheel_count;

void Init_Serial_UCA0(void){ //IOT Module
//------------------------------------------------------------------------------
//                                                               TX error (%) RX error (%)
// BRCLK     Baudrate     UCOS16     UCBRx     UCFx     UCSx     neg   pos    neg   pos
// 8000000   4800           1         104       2       0xD6    -0.08 0.04   -0.10 0.14
// 8000000   9600           1         52        1       0x49    -0.08 0.04   -0.10 0.14
// 8000000   19200          1         26        0       0xB6    -0.08 0.16   -0.28 0.20
// 8000000   57600          1         8         10      0xF7    -0.32 0.32   -1.00 0.36
// 8000000   115200         1         4         5       0x55    -0.80 0.64   -1.12 1.76
// 8000000   460800         0         17        0       0x4A    -2.72 2.56   -3.76 7.28
//------------------------------------------------------------------------------
// Configure eUSCI_A1 for UART mode
UCA0CTLW0 = 0;
UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
UCA0CTLW0 &= ~UCPEN; // No Parity
UCA0CTLW0 &= ~UCSYNC;
UCA0CTLW0 &= ~UC7BIT;
UCA0CTLW0 |= UCMODE_0;
// BRCLK     Baudrate     UCOS16     UCBRx     UCFx     UCSx     neg  pos    neg   pos
// 8000000   115200         1          4        5       0x55    -0.80 0.64  -1.12  1.76
// UCA?MCTLW = UCSx + UCFx + UCOS16
UCA0BRW = 4 ; // 115,200 baud
UCA0MCTLW = 0x5551 ;
UCA0CTLW0 &= ~UCSWRST ; // release from reset
//UCA1TXBUF = 0x00; // Prime the Pump
UCA0IE |= UCRXIE; // Enable RX interrupt

}

void Init_Serial_UCA1(void){
//------------------------------------------------------------------------------
//                                                               TX error (%) RX error (%)
// BRCLK     Baudrate     UCOS16     UCBRx     UCFx     UCSx     neg   pos    neg   pos
// 8000000   4800           1         104       2       0xD6    -0.08 0.04   -0.10 0.14
// 8000000   9600           1         52        1       0x49    -0.08 0.04   -0.10 0.14
// 8000000   19200          1         26        0       0xB6    -0.08 0.16   -0.28 0.20
// 8000000   57600          1         8         10      0xF7    -0.32 0.32   -1.00 0.36
// 8000000   115200         1         4         5       0x55    -0.80 0.64   -1.12 1.76
// 8000000   460800         0         17        0       0x4A    -2.72 2.56   -3.76 7.28
//------------------------------------------------------------------------------
// Configure eUSCI_A1 for UART mode
UCA1CTLW0 = 0;
UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
UCA1CTLW0 &= ~UCPEN; // No Parity
UCA1CTLW0 &= ~UCSYNC;
UCA1CTLW0 &= ~UC7BIT;
UCA1CTLW0 |= UCMODE_0;
// BRCLK     Baudrate     UCOS16     UCBRx     UCFx     UCSx     neg  pos    neg   pos
// 8000000   115200         1          4        5       0x55    -0.80 0.64  -1.12  1.76
// UCA?MCTLW = UCSx + UCFx + UCOS16
UCA1BRW = 4 ; // 115,200 baud
UCA1MCTLW = 0x5551 ;
UCA1CTLW0 &= ~UCSWRST ; // release from reset
//UCA1TXBUF = 0x00; // Prime the Pump
UCA1IE |= UCRXIE; // Enable RX interrupt

}

void Init_Serial_Ports(){
  Init_Serial_UCA0();
  Init_Serial_UCA1();
  
}

#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
//-----------------------------------------------------------------------------
// Echo back RXed character, confirm TX buffer is ready first
  unsigned int temp = 0;
  switch(__even_in_range(UCA0IV,0x08)){
    case 0: break; // Vector 0 - no interrupt
    case 2: // Vector 2 - RXIFG
      temp = iot_rx_wr++;
      IOT_2_PC[temp] = UCA0RXBUF; // Rx -> IOT_2_PC character array
      if (iot_rx_wr >= (sizeof(IOT_2_PC))){
        iot_rx_wr = BEGINNING; // Circular buffer back to beginning
      }
      UCA1IE |= UCTXIE; // Enable Tx interrupt
      break;
    case 4: // Vector 4 - TXIFG
      UCA0TXBUF = PC_2_IOT[direct_iot++];
      if (direct_iot >= (sizeof(PC_2_IOT))){
        direct_iot = BEGINNING;
      }
      if (direct_iot == usb_rx_wr){
        UCA0IE &= ~UCTXIE; // Disable TX interrupt
      }
      break;
    default: break;
}
//------------------------------------------------------------------------------
}

#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
//------------------------------------------------------------------------------
// Echo back RXed character, confirm TX buffer is ready first
  unsigned int temp = 0;
  switch(__even_in_range(UCA1IV,0x08)){
    case 0: break; // Vector 0 - no interrupt
    case 2: // Vector 2 - RXIFG
      temp = usb_rx_wr++;
      PC_2_IOT[temp] = UCA1RXBUF; // Rx -> PC_2_IOT character array
      if (usb_rx_wr >= (sizeof(PC_2_IOT))){
        usb_rx_wr = BEGINNING; // Circular buffer back to beginning
      }
      UCA0IE |= UCTXIE; // Enable Tx interrupt
      break;
    case 4: // Vector 4 - TXIFG
      UCA1TXBUF = IOT_2_PC[direct_usb++];
      if (direct_usb >= (sizeof(IOT_2_PC))){
        direct_usb = BEGINNING; // Circular buffer back to beginning
      }
      if (direct_usb == iot_rx_wr){
        UCA1IE &= ~UCTXIE; // Disable TX interrupt
      }
      break;
    default: break;
  }
}

         
void Clear_A1_Process_Buffer(){
  for (int i=0;i<sizeof(A1_Process_Buffer);i++){
    A1_Process_Buffer[i]=0;
  }
}

void Clear_A0_Process_Buffer(){
  for (int i=0;i<sizeof(A0_Process_Buffer);i++){
    A0_Process_Buffer[i]=0;
  }
}

void Clear_PC_2_IOT(){
  for (int i=0;i<sizeof(PC_2_IOT);i++){
    PC_2_IOT[i]=0;
  }
}

void Clear_IOT_2_PC(){
  for (int i=0;i<sizeof(IOT_2_PC);i++){
    IOT_2_PC[i]=0;
  }
}

void IOT_Process(void){ // Process IOT messages
  unsigned int iot_rx_wr_temp;
  iot_rx_wr_temp = iot_rx_wr;
  if(iot_rx_wr_temp != iot_rx_rd){ // Determine if IOT is available
    A0_Process_Buffer[A0_position++] = IOT_2_PC[iot_rx_rd++];
    if(iot_rx_rd >= sizeof(IOT_2_PC)){
      iot_rx_rd = BEGINNING;
    }
 
  }
  
  else{
    if(strstr(A0_Process_Buffer,"ready")){
      P6OUT |= GRN_LED;  //Turn on green LED
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    }
    
    if(strstr(A0_Process_Buffer,"GOT IP")){
      TB1CCTL1 |= CCIE; // CCR1 enable interrupt
      P1OUT &= ~RED_LED; // Turn Red LED off
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    }
    
   if(strstr(A0_Process_Buffer,"IP") && strstr(A0_Process_Buffer,"MAC")){ //find IP address in the quotes
      Clear_Display();
      strcpy(display_line[0],"   ncsu   ");
      strcpy(display_line[1],"IP Address");
      display_changed=TRUE;
      ipstr1=strstr(A0_Process_Buffer,"\"")+1;
      dot2=strstr(ipstr1,DOT);
      dot2=strstr(dot2+1,DOT);
      size=dot2 + 1 - ipstr1;
 
      strncpy(&display_line[2][1], ipstr1,size); 
      display_changed=TRUE;
      
      ipstr2=dot2+1;
      end=strtok(ipstr2,"\"");
      strcpy(&display_line[3][1], ipstr2);
      display_changed=TRUE;
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    
      }
    
    if(strstr(A0_Process_Buffer,"^2002F0000")){
      TB1CCTL0 &= ~CCIE;
      wheels_forward_slow();
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    }
    if(strstr(A0_Process_Buffer,"^2002F1000")){
      TB1CCTL0 &= ~CCIE;
      line_status=OFF;
      wheels_forward_fast();
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    }
    if(strstr(A0_Process_Buffer,"^2002S0000")){
      TB1CCTL0 &= ~CCIE;
      P2OUT &= ~IR_LED;
      wheels_off();
      line_status=OFF;
      Clear_Display();
      strcpy(display_line[2],"BL STOP!  ");
      display_changed=TRUE;
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    }
    
    if(strstr(A0_Process_Buffer,"^2002S1000")){
      TB1CCTL0 &= ~CCIE;
      P2OUT &= ~IR_LED;
      wheels_off();
      line_status=OFF;
      Clear_Display();
      strcpy(display_line[2],"BL CIRCLE  ");
      display_changed=TRUE;
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    }
    if(strstr(A0_Process_Buffer,"^2002B0000")){
      TB1CCTL0 &= ~CCIE;
      wheels_reverse_slow();
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    }
    if(strstr(A0_Process_Buffer,"^2002L0000")){
      TB1CCTL0 &= ~CCIE;
      left_turn();
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    }
    if(strstr(A0_Process_Buffer,"^2002R0000")){
      TB1CCTL0 &= ~CCIE;
      right_turn();
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    }
    if(strstr(A0_Process_Buffer,"^2002L1000")){
      TB1CCTL0 &= ~CCIE;
      left_turn_sharp();
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    }
    if(strstr(A0_Process_Buffer,"^2002R1000")){
      TB1CCTL0 &= ~CCIE;
      right_turn_sharp();
      Clear_A0_Process_Buffer();
      A0_position=0;
    }
    if(strstr(A0_Process_Buffer,"^2002A0000")){
      TB1CCTL0 &= ~CCIE;
      wheels_off();
      Clear_Display();
      arrive_counter++;
      strcpy(display_line[0],"  JUSTIN  ");
      strcpy(display_line[1]," DHILLION ");     
      strcpy(display_line[2],"ARRIVED AT");
      display_line[3][5]=arrive_counter + ASCII_ADJUST;  
      display_changed=TRUE;
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    }
    if(strstr(A0_Process_Buffer,"^2002A1000")){
      wheels_off();
      Clear_Display();
      arrive_counter--;
      strcpy(display_line[0],"  JUSTIN  ");
      strcpy(display_line[1]," DHILLION ");     
      strcpy(display_line[2],"ARRIVED AT");
      display_line[3][5]=arrive_counter + ASCII_ADJUST;  
      display_changed=TRUE;
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
    }
    if(strstr(A0_Process_Buffer,"^2002C0000")){
      TB1CCTL0 |= CCIE; // CCR0 enable interrupt
      P2DIR |= IR_LED;
      P2OUT |= IR_LED;
      ADCCTL0 |= ADCENC;     // ADC enable conversion.
      ADCCTL0 |= ADCSC;
      Clear_Display();
      strcpy(display_line[0],"Justin    ");     
      strcpy(display_line[1],"Dhillion  ");
      lcd_BIG_bot();
      strcpy(display_line[2],"BL START  ");
      display_changed=TRUE;
      Clear_A0_Process_Buffer();
      A0_position=BEGINNING;
      line_status=START;
      wheel_count=OFF;
    }
   }
  }
  
      
      
      
      
    


       

void IOT_BOOTUP(){ //This sends the IOT the base commands like assigning port number, and getting IP
    
    switch(boot_state){
      case (BOOTUP):
        if(command_counter==FIRSTCOMMAND){
          Clear_PC_2_IOT();
          strncpy(display_line[1]," Running  ",sizeof(display_line[1]));
          strncpy(display_line[2],"  CIPMUX  ",sizeof(display_line[2]));
          display_changed=TRUE;
          strcpy((char*)PC_2_IOT,MULTICONN);
          boot_state=SERVER;
          UCA0IE |= UCTXIE;
          Clear_A0_Process_Buffer();
          A0_position=BEGINNING;
        }

        break;
        
      case(SERVER):
        
        if(command_counter==SECONDCOMMAND){
          Clear_PC_2_IOT();
          strncpy(display_line[1]," Setting  ",sizeof(display_line[1]));
          strncpy(display_line[2],"   Port   ",sizeof(display_line[2]));
          display_changed=TRUE;
          strcpy((char*)PC_2_IOT,PORT);
          boot_state=IP;
          UCA0IE |= UCTXIE;
          Clear_A0_Process_Buffer();
          A0_position=BEGINNING;
        }
        break;
        

      case (IP):

        if(command_counter==THIRDCOMMAND){
          Clear_PC_2_IOT();
          strcpy((char*)PC_2_IOT,IP_Command);
          UCA0IE |= UCTXIE;
          boot_state=END;
          command_counter=OFF;
          command_done=DONE;
          state=DONE;
        }
        break;
          
      default:
        Clear_PC_2_IOT();
        break;
   
    }
}     

