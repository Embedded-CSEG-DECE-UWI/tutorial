#include <p18cxxx.h>            //includes library to use features of pic18
#include <delays.h>             //includes library to use delay functions

//#define _XTAL_FREQ 4000000

/*Configuration pragmas for the c18 C compiler*/
#pragma config OSC = XT         //Oscillator set to external
#pragma config WDT = OFF        //Watchdog Timer OFF
#pragma config LVP = OFF        //Low Voltage Programming OFF

typedef int bool;               //defining a new data type with additional keywords
#define true 1
#define false 0;

void main(void){
    
    bool isWorking = true;      //initializes the variable to true
    
    TRISB = 0x00;               //configures all the TRISB bits as outputs
   
    while(isWorking){           //while this condition is the same, the block of code is repeated
        PORTB = 0xFF;           //sets PORTB to high (this turns the LED on) 
        Delay10KTCYx(100);      //delays for 1 sec
        PORTB = 0x00;           //sets PORTB to low (this turns the LED off)
        Delay10KTCYx(100);
    }
    Sleep();
}
