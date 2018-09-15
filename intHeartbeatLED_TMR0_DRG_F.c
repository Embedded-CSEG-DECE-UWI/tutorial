/* 
 * File:   intHeartbeatLED_TMR0_DRG_F.c
 * Author: 816000924
 *
 * Created on September 15, 2018, 3:58 AM
 * 
 * This program uses TMR0 to implement a heartbeat LED on overflow while 
 * maintaining another LED in the ON state within the main function. This
 * is an example of an internal Heartbeat LED
 */
#include <p18cxxx.h>
#include <delays.h>

//Configuration pragma statements
#pragma config OSC = XT
#pragma config WDT = OFF
#pragma config LVP = OFF

//Function prototypes
void toggle_LED(void);
void configInterrupts(void);
void configTMR0(void);

int counter = 0;                                    //declares and initializes a global counter to aid in accurate timing

#pragma code HIGH_INTERRUPT_VECTOR = 0x08           //tells the compiler that the high interrupt vector is located at 0x09
void high_ISR(void){                                //high interrupt vector ISR
    _asm                                            //allows asm code to be used into a C source file
    goto toggle_LED                                 //goes to interrupt routine
    _endasm                                         //ends asm code insertion
}
#pragma code

#pragma interrupt toggle_LED
void toggle_LED(void){                              //interrupt handler to blink heartbeat LED
    counter++;
    INTCONbits.GIE = 0;                             //disables interrupt sources while in handler to prevent possible looping
    INTCONbits.TMR0IE = 0;
 
    /*
     * The count 4 was used because since the pre-scaler is 1:4 and it takes 65536us for TMR0 to overflow without a pre-scaler,
     * with the pre-scaler it would take 262144us. Therefore, by counting 3.8 (approximately 4 times), the LED will blink every 
     * 1000000us or 1s
     */
    if((INTCONbits.TMR0IF == 1)&&(counter == 4)){   //checks the status of the TMR0 interrupt flag and that the counter has incremented to 4
        PORTBbits.RB4 = 1;                          //blinks the LED if the flag was set
        Delay10KTCYx(20);
        counter = 0;                                //resets the counter
    }
    INTCONbits.TMR0IF = 0;                          //clears the interrupt flag
    INTCONbits.GIE = 1;                             //re-enables interrupt sources on exit from the handler
    INTCONbits.TMR0IE = 1;
}

//Main function
void main(void){
    configInterrupts(); 
    configTMR0();
    T0CONbits.TMR0ON = 1;                           //enables the TMR0 to begin timing
    
    TRISB = 0x00;                                   //configures the TRISB ports as outputs
    
    while(1){
        PORTBbits.RB4 = 0;                          //maintain LED1 in the OFF state
        PORTBbits.RB5 = 1;                          //maintain LED2 in the ON state
    }
}

//function to configure the necessary interrupt bits
void configInterrupts(void){
    RCONbits.IPEN = 1;                              //allows the priority level interrupts to be used
    INTCONbits.GIE = 1;                             //enables global interrupt sources
    INTCONbits.TMR0IE = 1;                          //enables the TMR0 interrupt source
}

//function to configure TMR0
void configTMR0(void){
    T0CONbits.TMR0ON = 0;                           //ensures TMR0 is off
    T0CONbits.T08BIT = 0;                           //sets the TMR0 for use in 16-bit mode
    T0CONbits.T0CS = 0;                             //uses the internal clock of the PIC to increment TMR0
    T0CONbits.PSA = 0;                              //enables a pre-scaler to be used 
    
    T0CONbits.T0PS2 = 0;                            //these 3-bits enables the pre-scalar ratio to be set (in this case 1:8)
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS0 = 1;
}

