/* Lab 1 first file - ID number 815006394 Group A   */
#include <p18cxxx.h>   
#include <delays.h>

/* Set configuration bits for use with PICKit3 and 4MHz oscillator */
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

//#define XTAL_FREQ 4000000

int count;
void main (void)
{
    /* Insert code from pre-lab Q14 to change values on PORTB */
    //count = 1;
    TRISB = 0;      //config PORTB as output
    for(count = 1; count<=15; count++)
    {
        PORTB = count;  //displays count
        Delay10KTCYx (25);
    }
}