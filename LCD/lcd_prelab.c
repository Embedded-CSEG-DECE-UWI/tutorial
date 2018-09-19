/* Lab 1 first file - ID number 816000924 Group F  */
#include <p18f452.h> 
#include <delays.h>
#include "xlcd.h"

 /* Set configuration bits for use with PICKit3 and 4MHz oscillator */
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000

void DelayFor18TCY(void)
 {

         Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
         Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
         
 }
 
 void DelayXLCD(void){                  //1000us = 1ms
     Delay1KTCYx(5);
     
 }
 
 void DelayPORXLCD(void){
     Delay1KTCYx(15);
 }
 
  void init_lcd(void)
{ 

     OpenXLCD(FOUR_BIT & LINES_5X7);
     //while(BusyXLCD());
     //WriteCmdXLCD(FOUR_BIT & LINES_5X7);
     //while(BusyXLCD());
     //WriteCmdXLCD( BLINK_ON );
     while(BusyXLCD());
     WriteCmdXLCD(SHIFT_DISP_LEFT);
}

 
 void main (void)
 {
     init_lcd();
     while(BusyXLCD());
     SetDDRamAddr(0x00);
     putrsXLCD("Hola Mundo");
     while (1)
     {}
 }