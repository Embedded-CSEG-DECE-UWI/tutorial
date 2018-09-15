#include <p18cxxx.h>
#include <delays.h>

#pragma config OSC = XT
#pragma config WDT = OFF
#pragma config LVP = OFF
//#pragma config DEBUG = ON

void toggle_LED(void);
void configInterrupts(void);
void configTMR0(void);

#pragma code HIGH_INTERRUPT_VECTOR = 0x08
void high_ISR(void){
    _asm
    goto toggle_LED
    _endasm
}
#pragma code

#pragma interrupt toggle_LED
void toggle_LED(void){
    INTCONbits.GIE = 0;
    INTCONbits.TMR0IE = 0;
    
    if(INTCONbits.TMR0IF == 1){
        PORTBbits.RB4 = 1;
        Delay10KTCYx(20);
    }
    INTCONbits.TMR0IF = 0;
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;
}

void main(void){
    configInterrupts(); 
    configTMR0();
    T0CONbits.TMR0ON = 1;
    
    TRISB = 0x00;
    
    while(1){
        PORTBbits.RB4 = 0;
        PORTBbits.RB5 = 1;
    }
}

void configInterrupts(void){
    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;    
}

void configTMR0(void){
    T0CONbits.TMR0ON = 0;
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS2 = 0;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS0 = 0;
}

