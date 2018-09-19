/* Lab 1 first file - ID number 815006394 Group A   */
#include <p18f452.h>   
#include <delays.h>
#include "xlcd_A.h"
#include <string.h>
#include <stdio.h>

/* Set configuration bits for use with PICKit3 and 4MHz oscillator */
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

//#define _XTAL_FREQ 4000000UL

#define l1  0x01    //addresses of the beginning of line1
#define l2  0x40    //addresses of the beginning of line2
#define l3  0x14    //addresses of the beginning of line3
#define l4  0x54    //addresses of the beginning of line4
char cgaddr = 0xCF;
const char LCDbuf = "H";
const rom char Title = "P";
int i;

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

void setup(void)
{
    PORTD = 0;
    TRISD = 0;
    //LATEbits.LATE = 0;
    OpenXLCD(FOUR_BIT & LINES_5X7);        //config LCD for 4-bit operation and two-line display
    //while (BusyXLCD());
    //WriteCmdXLCD(FOUR_BIT & LINES_5X7);
    //while(BusyXLCD());
    //WriteCmdXLCD(BLINK_ON);
    //while(BusyXLCD());
    //WriteCmdXLCD(0x01);
    //while(BusyXLCD());
    SetDDRamAddr(l1);                       //starting point on second line
    //for (i=0;i<4;i++)
     //   WriteCmdXLCD(SHIFT_DISP_RIGHT);     //shifts to the left 4 times
    //WriteCmdXLCD(BLINK_ON);
    //while(BusyXLCD());
}


void main(void)
{
    setup();
    while(1)
    {
        //while (BusyXLCD());     //returns 1 if busy
        //putsXLCD(LCDbuf);       //PreLab Q18d
        putrsXLCD(Title); 
        //SetCGRamAddr(cgaddr);
        Nop();
    }
    //while(BusyXLCD());
    //putrsXLCD(Title);       //PreLab Q18e
    
    //while(BusyXLCD());
    Sleep();
}
