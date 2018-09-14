/* Lab 1 first file - ID number 815006394 Group A   */
#include <p18cxxx.h>   
#include <delays.h>
#include <xlcd.h>
#include <usart.h>

/* Set configuration bits for use with PICKit3 and 4MHz oscillator */
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

#define l1  0x00
#define l2  0x40
#define l3  0x14
#define l4  0x54



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
void Delayvoid DelayXLCD (void)
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
    //PreLab Q18a
    //config LCD for 4-bit operation and two-line display
    OpenXLCD (FOUR_BIT & LINES_5X7);
    
    //Prelab Q18b
    //block execution when LCD is busy
    while (BusyXLCD());     //returns 1 if busy
    {
        //insert task to be performed if LCD is not busy
        SetDDRamAddr(l2);       //PreLab Q18c
        for (i=0;i<4;i++)
            WriteCmdXLCD(SHIFT_DISP_RIGHT);
        putsXLCD(LCDbuf);       //PreLab Q18d
        putrsXLCD(Title);       //PreLab Q18e
    }
}
