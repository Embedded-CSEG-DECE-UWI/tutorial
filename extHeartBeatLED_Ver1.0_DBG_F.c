/* 
 * File:   extHeartBeatLED_Ver1.0_DBG_F
 * Author: 816002553
 *
 * Created on September 14, 2018, 2:31 PM
 * 
 * This program will read the value of a switch connect to the PIC to send a
 * HIGH or LOW through a GPIO pin to switch ON/OFF an external heartbeat LED 
 * which will indicate that the system is functioning.
 * 
 */
#include <p18cxxx.h>            //includes library to use features of pic18



/*Configuration pragmas for the c18 C compiler*/
#pragma config OSC = XT         //Oscillator set to external
#pragma config WDT = OFF        //Watchdog Timer OFF
#pragma config LVP = OFF        //Low Voltage Programming OFF

/*
 * 
 */

int isSwitchOn()
{   
    return PORTBbits.RB2;            //Returns the current state of the switch
}

void setTransistorSwitch(int val)
{
    if(val == 1) 
        PORTBbits.RB3 = 1;
    else if (val == 0) 
        PORTBbits.RB3 = 0  ;
}

void configPins()
{
    TRISBbits.RB2 = 1;              //INPUT: Switch
    TRISBbits.RB3 = 0;              //OUTPUT: Signal to the transistor
    TRISBbits.RB4 = 0;              //OUTPUT: Green LED
}


int main() 
{
    if (isSwitchOn)
    {
        setTransistorSwitch(1);//Send a HIGH to PIN XX
    }
    else
    {
        setTransistorSwitch(0);//Send a LOW to PIN XX
    }
   
    return 0;
}

