/* Lab 1 first file - ID number 815006394 Group A   */
#include <p18cxxx.h>   
#include <delays.h>
#include "xlcd_A.h"
#include <string.h>
#include <stdio.h>

/* Set configuration bits for use with PICKit3 and 4MHz oscillator */
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000UL

#define l1  0x00    //addresses of the beginning of line1
#define l2  0x40    //addresses of the beginning of line2
#define l3  0x14    //addresses of the beginning of line3
#define l4  0x54    //addresses of the beginning of line4

const char LCDbuf[12] = "Hello World";
const rom char Title[14] = "Program memory";
int i;

//LATDbits.LATD0 = E_PIN;
/*PORTDbits.RD0 = E_PIN;
PORTDbits.RD1 = RS_PIN;
PORTDbits.RD2 = RW_PIN;
PORTD = DATA_PORT;
/*#define DB4_PIN = PORTbits.RD4;
#define DB5_PIN = PORTbits.RD5;
#define DB6_PIN = PORTbits.RD6;
#define DB7_PIN = PORTbits.RD7;*/

/*void configPins()
{

    PORTDbits.RD0 = E_PIN;
    PORTDbits.RD1 = RS_PIN;
    PORTDbits.RD2 = RW_PIN;
    PORTD = DATA_PORT;
}*/

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
}

//PreLab Q16b
void DelayXLCD (void)
{
    Delay1KTCYx(20);    // Delay of 5ms
                        // Cycles = (TimeDelay * Fosc) / 4
                        // Cycles = (5ms * 16MHz) / 4
                        // Cycles = 20,000
    return;
}

//PreLab Q16c
void DelayPORXLCD (void)
{
    Delay1KTCYx(60);    // Delay of 15ms
                        // Cycles = (TimeDelay * Fosc) / 4
                        // Cycles = (15ms * 16MHz) / 4
                        // Cycles = 60,000
    return;
}

void setup(void)
{
    PORTD = 0;
    TRISD = 0;
    
    OpenXLCD (FOUR_BIT & LINES_5X7);        //config LCD for 4-bit operation and two-line display
    while (BusyXLCD());
    SetDDRamAddr(l1);                       //starting point on second line
    for (i=0;i<4;i++)
        WriteCmdXLCD(SHIFT_DISP_RIGHT);     //shifts to the left 4 times
    WriteCmdXLCD(BLINK_ON);
}


void main(void)
{
    setup();
    while (BusyXLCD());     //returns 1 if busy
    putsXLCD(LCDbuf);       //PreLab Q18d
    while(BusyXLCD());
    putrsXLCD(Title);       //PreLab Q18e
    while(BusyXLCD());
    Sleep();
}
