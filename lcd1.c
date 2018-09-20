#include<p18cxxx.h>
#include<delays.h>
#include "xlcd_A.h"


/* Set configuration bits for use with PICKit3 and 4MHz oscillator */
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000

#define l1  0x00    //addresses of the beginning of line1
#define l2  0x40    //addresses of the beginning of line2
#define l3  0x10    //addresses of the beginning of line3
#define l4  0x50    //addresses of the beginning of line4

//PreLab Q16a
void DelayFor18TCY(void)
{
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
}

//PreLab Q16b
void DelayXLCD (void)
{
    Delay1KTCYx(5);    
    return;
}

//PreLab Q16c
void DelayPORXLCD (void)
{
    Delay1KTCYx(15);    
    return;
}

void setup (void)
{
    while(BusyXLCD());
    OpenXLCD(FOUR_BIT & LINES_5X7); 
    DelayPORXLCD();
    while(BusyXLCD());
    SetDDRamAddr(l2);  
}

void main (void)
{
    setup();
    //DelayPORXLCD();
    while(BusyXLCD());
    putrsXLCD("Hello World");
    while(1){}
}