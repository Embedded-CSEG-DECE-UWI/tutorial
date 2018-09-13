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
        cnt++ ;
                
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
  T0CONbits.TMR0ON = 0;              //Turn off timer0
  T0CONbits.T08BIT = 0;              //Set timer to 16 bit mode
  T0CONbits.T0CS = 0;                //Set to timer source to internal
  T0CONbits.T0SE = 0;                //Clear PSA bit
  T0CONbits.T0PS = 0;                //Set prescalar to 2
  T0CONbits.PSA = 0;                 //Timer0 prescalar assigned
  WriteTimer0(25535);                //Load Timer0
  INTCON2bits.TMR0IP = 0;            //Disable high priority interrupt             
  T0CONbits.TMR0ON = 1;              //Turn on Timer0
  INTCONbits.TMR0IE = 1;             //Set the Timer0 Interrupt Enable Bit
  INTCONbits.PEIE = 1;               //Enable Peripheral Interrupt
  INTCONbits.GIE =1;                 //Enable Global Interrupt Enable bit
}




void main(void)
{
    TRISBbits.RB4 = 0;          //configures RB4 as an OUTPUT the TRISB bits as outputs
    configTimer();              //Set the timer up for 1 second
    while(1)                    //Infinite Loop
    {
        if(INTCONbits.TMR0IF == 1)
            toggleBit();
    }
    //Sleep();                    //Puts the microprocessor to sleep mode
}





