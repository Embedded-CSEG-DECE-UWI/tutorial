#include <p18cxxx.h>            //includes library to use features of pic18
#include <delays.h>             //includes library to use delay functions

//#define _XTAL_FREQ 4000000

/*Configuration pragmas for the c18 C compiler*/
#pragma config OSC = XT         //Oscillator set to external
#pragma config WDT = OFF        //Watchdog Timer OFF
#pragma config LVP = OFF        //Low Voltage Programming OFF

/*FUNCTION PROTOTYPES*/
void toggleBit();
void blinkLED();
void checkSwitch();

typedef int bool;               //defining a new data type with additional keywords
#define true 1
#define false 0;

bool isWorking = true;          //initializes the variable to true

void main(void){
    TRISB = 0b0000100;          //configures TRISB bit 2 as an input and bit 4 as an output
   
    while(isWorking){           //keeps executing the block of code as long as the global variable has not been changed
        checkSwitch();          //checks the state of the switch and behaves accordingly
    }
    
    Sleep();                    //Puts the microprocessor in sleep mode
}

//Toggles the state of the bit
void toggleBit(){
    PORTBbits.RB4 = !PORTBbits.RB4;  
}

//Blinks the LED
void blinkLED(){
    toggleBit();                //calls the function to toggle the bit
    Delay10KTCYx(100);          //delays for 1 sec
    toggleBit();                //calls the function to toggle the bit
    Delay10KTCYx(100);          //delays for 1 sec
}

//Checks the status of the switch and behaves accordingly
void checkSwitch(){
    if(PORTBbits.RB2 == 1)      
        blinkLED();             //if the RB2 input reads HIGH (switch ON), blink
    else
        PORTBbits.RB4 = 0;      //else if the RB2 input reads LOW (switch OFF), turn off LED
}
