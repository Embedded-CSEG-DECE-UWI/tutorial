#include <p18cxxx.h>            //includes library to use features of pic18
#include <delays.h>             //includes library to use delay functions


/*Configuration pragmas for the c18 C compiler*/
#pragma config OSC = XT         //Oscillator set to external
#pragma config WDT = OFF        //Watchdog Timer OFF
#pragma config LVP = OFF        //Low Voltage Programming OFF

void toggleBit();               //Prototype needed for the 'goto' below

#pragma code HIGH_INTERRUPT_VECTOR = 0x8
void high_ISR()
{
    goto toggleBit();
}
#pragma code                    //Allows the linker to locate the remaining code

#pragma interrupt toggleBit
//Toggles the state of the bit`
void toggleBit()
{
    PORTBbits.RB4 = !PORTBbits.RB4; 
    //Reset the interrupt for the timer;
}

void configTimer()
{}

void configGlobalInterrupts()
{}


void main(void)
{
    TRISB = 0x00;               //configures all the TRISB bits as outputs
    configTimer();              //Set the timer up for 1 second
    configGloabalInterrupts();  //Set the global interrupt for operation
    while(1)                    //Infinite Loop
    Sleep();                    //Puts the microprocessor to sleep mode
}





