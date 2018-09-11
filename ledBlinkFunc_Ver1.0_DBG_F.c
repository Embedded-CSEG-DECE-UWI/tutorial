#include <p18cxxx.h>            //includes library to use features of pic18
#include <delays.h>             //includes library to use delay functions

/*Configuration pragmas for the c18 C compiler*/
#pragma config OSC = XT         //Oscillator set to external
#pragma config WDT = OFF        //Watchdog Timer OFF
#pragma config LVP = OFF        //Low Voltage Programming OFF

void toggleBit();               //Prototype of the toggleBit fucntion

void main(void)
{
    TRISB = 0x00;               //configures all the TRISB bits as outputs
   
    while(1)                    //while this condition is the same, the block of code is repeated
    {
        toggleBit();            //calls the function to toggle the bit
        Delay10KTCYx(100);      //delays for 1 sec
        toggleBit();            //calls the function to toggle the bit
        Delay10KTCYx(100);      //delays for 1 sec
    }
    Sleep();                    //Puts the microprocessor to sleep mode
}

//Toggles the state of the bit
void toggleBit(){
    PORTBbits.RB4 = !PORTBbits.RB4; 
}   

