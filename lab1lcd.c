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

#define l1  0x00    //addresses of the beginning of line1
#define l2  0x40    //addresses of the beginning of line2
#define l3  0x14    //addresses of the beginning of line3
#define l4  0x54    //addresses of the beginning of line4

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

const char LCDbuf[20] = "Hello World";
const rom char Title[20] = "Program memory";
int i;

void main(void)
{
    //configPins();
    WriteCmdXLCD(BLINK_ON);
    //PreLab Q18a
    //config LCD for 4-bit operation and two-line display
    OpenXLCD (FOUR_BIT & LINES_5X7);
    SetDDRamAddr(l2);
    for (i=0;i<4;i++)
        WriteCmdXLCD(SHIFT_DISP_RIGHT);
    //Prelab Q18b
    //block execution when LCD is busy
    //config USART
    //OpenUSART (USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX, 25);
    while (BusyXLCD());     //returns 1 if busy
    //insert task to be performed if LCD is not busy
    //SetDDRamAddr(l2);       //PreLab Q18c - beginning at line 2
    //for (i=0;i<4;i++)
    //    WriteCmdXLCD(SHIFT_DISP_RIGHT);     //
    putsXLCD(LCDbuf);       //PreLab Q18d
    //for(i=0;i<11;i++)
    //    DelayPORXLCD();
    while(BusyXLCD());
    putrsXLCD(Title);       //PreLab Q18e
    Sleep();
    
}
