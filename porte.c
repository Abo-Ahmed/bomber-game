

#include "porte.h"


// Subroutine enables interrupt
// Inputs:  none
// Outputs: none
// Notes:   friendly means it does not affect other bits in the port

void init_interrupt(void)
{
	GPIOE->IS &= ~  ( ( 1 << 0 ) |  ( 1 << 4 ) )  ;
	GPIOE->IBE &= ~ ( ( 1 << 0 ) | ( 1 << 4 )  ) ;
	GPIOE->IEV &= ~ ( ( 1 << 0 ) |  ( 1 << 4) ) ;
	GPIOE->ICR |=  ( 1 << 0 ) | ( 1 << 4)   ;
	GPIOE->IM |=   ( 1 << 0 ) | ( 1 << 4);
	NVIC->ISER [0] = 1 << 4; 
	// enable interrupts for the grader

}	


// Subroutine acknowlege the interrupt on portE
// Inputs:  none
// Outputs: none
// Notes:   friendly means it does not affect other bits in the port
void interrupt_ackn(void)
{
GPIOE->ICR |=  ( 1 << 0 ) | ( 1 << 4)   ;
}


/**
function: portE_init
input
output
notes
**/
void PortE_Init(void){ 
	volatile unsigned long delay;
  SYSCTL->RCGC2 |= 0x00000010;      // 1) E clock
  delay = SYSCTL->RCGC2;            // delay to allow clock to stabilize 	
  GPIOE->AMSEL = 0x00;        // 2) disable analog function
  GPIOE->PCTL = 0x00000000;   // 3) GPIO clear bit PCTL  
  GPIOE->DIR &= ~0x11;         // 4.1) PE0 , 4 input,
	GPIOE->AFSEL = 0x00;        // 5) no alternate function
  GPIOE->PUR = 0x00;         	 // 6) disable pullup resistor on PE0       
  GPIOE->DEN |= 0xff;          // 7) enable digital pins PE4-PE0
}

