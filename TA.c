//this is sample code
#include <p18cxxx.h>
#include <p18f452.h>

#pragma config OSC = XT, OSCS = OFF
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config WDT = OFF
#pragma config CCP2MUX = OFF
#pragma config LVP = OFF

void delay (void)
{
  int i;

  for (i = 0; i < 10000; i++)
    ;
}

void main (void)
{
  
  TRISD = 0x00;

  while (1)
    {
      /* Reset the LEDs */
      PORTD = 0x00;

      /* Delay so human eye can see change */
      delay ();

      /* Light the LEDs */
      PORTD = 0x80;

      /* Delay so human eye can see change */
      delay ();
    }
}
