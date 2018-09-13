#include <p18cxxx.h>            //includes library to use features of pic18
#include <delays.h>             //includes library to use delay functions
#include <timers.h>             //includes library to use timer functions    

/*Configuration pragmas for the c18 C compiler*/
#pragma config OSC = XT         //Oscillator set to external
#pragma config WDT = OFF        //Watchdog Timer OFF
#pragma config LVP = OFF        //Low Voltage Programming OFF

int cnt = 0;
void low_isr();
void toggleBit();

#pragma code low_vector = 0x18
void high_ISR()
{
    _asm
      GOTO low_isr
    _endasm
}
#pragma code                    //Allows the linker to locate the remaining code

#pragma interruptlow low_isr
void low_isr()
{
    if(INTCONbits.TMR0IF == 1)
    {
        if(cnt == 100)
        {
            cnt = 0;
            toggleBit();
            WriteTimer0(25535);
        }
        INTCONbits.TMR0IF = 0;
    }
}
//Toggles the state of the bit`
void toggleBit()
{
    PORTBbits.RB4 = !PORTBbits.RB4; 
    //Reset the interrupt for the timer;
}

void configTimer()
{
  //Turn off timer0
  //Set timer to 16 bit mode
  //Set to timer source to internal
  //Clear PSA bit
  //Set prescalar to 2
  //Load Timer0
  //Turn on Timer0
  //Set the Timer0 Interrupt Enable Bit
  //Enable Peripheral Interrupt
  //Enable Global Interrupt Enable bit
}




void main(void)
{
    TRISB = 0x00;               //configures all the TRISB bits as outputs
    configTimer();              //Set the timer up for 1 second
    configGloabalInterrupts();  //Set the global interrupt for operation
    while(1)                    //Infinite Loop
    Sleep();                    //Puts the microprocessor to sleep mode
}





