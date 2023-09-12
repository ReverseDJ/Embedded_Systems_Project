#include "functions.h"
#include "macros.h"
#include  "msp430.h"
#include <string.h>
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern char display_line[4][11];

//function clears display;
void Clear_Display(){
  strcpy(display_line[0], "          ");
  strcpy(display_line[1], "          ");
  strcpy(display_line[2], "          ");
  strcpy(display_line[3], "          ");
  display_changed=TRUE;
}

//function updates the display
void Display_Process(){
 
  if(update_display){
    update_display = 0;
    if(display_changed){
      display_changed = 0;
      Display_Update(0,0,0,0);
    }
  }
}

//-----------------------------------------------------------------
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//-----------------------------------------------------------------
char adc_char[4];

void HEXtoBCD(unsigned int hex_value){
  int value=0;
  for(int i=0; i < 4; i++) {
    adc_char[i] = 48;
  }
  while (hex_value > 999){
    hex_value = hex_value - 1000;
    value++;
    adc_char[0] = 48 + value;
  }
  value = 0;
  while (hex_value > 99){
    hex_value = hex_value - 100;
    value++;
    adc_char[1] = 48 + value;
  }
  value = 0;
  while (hex_value > 9){
    hex_value = hex_value - 10;
    value++;
    adc_char[2] = 48 + value;
  }       
  adc_char[3] = 48 + hex_value;
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Hex to BCD Conversion for timer
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//-----------------------------------------------------------------
char adc_char_t[5];

void HEXtoBCD_timer(unsigned int hex_value){
  int value=0;
  for(int i=0; i < 5; i++) {
    adc_char_t[i] = 48;
  }
  while (hex_value > 999){
    hex_value = hex_value - 1000;
    value++;
    adc_char_t[0] = 48 + value;
  }
  value = 0;
  while (hex_value > 99){
    hex_value = hex_value - 100;
    value++;
    adc_char_t[1] = 48 + value;
  }
  value = 0;
  while (hex_value > 9){
    hex_value = hex_value - 10;
    value++;
    adc_char_t[2] = 48 + value;
  }       
  
  adc_char_t[3] = 46; //"."
  adc_char_t[4] = 48 + hex_value;
}
//-----------------------------------------------------------------




