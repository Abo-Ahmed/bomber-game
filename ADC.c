

#include "ADC.h"


void ADC0_InitSWTriggerSeq3_Ch1(void){ volatile unsigned long delay;


  SYSCTL->RCGC2 |= 0x00000010;   // 1) activate clock for Port E

  delay = SYSCTL->RCGC2;         //    allow time for clock to stabilize

  GPIOE->DIR &= ~0x04;      // 2) make PE2 input
	
	//GPIOE->DIR |= 1 << 2;      // 2) make PE2 output

  GPIOE->AFSEL |= 0x04;     // 3) enable alternate function on PE2

  GPIOE->DEN &= ~0x04;      // 4) disable digital I/O on PE2

  GPIOE->AMSEL |= 0x04;     // 5) enable analog function on PE2

  SYSCTL->RCGC0 |= 0x00010000;   // 6) activate ADC0

  delay = SYSCTL->RCGC2;        

  SYSCTL->RCGC0 &= ~0x00000300;  // 7) configure for 125K

	ADC0->SSPRI  = 0x0123;          // 8) Sequencer 3 is highest priority

  ADC0->ACTSS &= ~0x0008;        // 9) disable sample sequencer 3

  ADC0->EMUX &= ~0xF000;         // 10) seq3 is software trigger

  ADC0->SSMUX3 &= (ADC0->SSMUX3 &0xFFFFFFF0)+1; // 11) channel Ain1 (PE3)


  ADC0->SSCTL3 = 0x0006;         // 12) no TS0 D0, yes IE0 END0

  ADC0->ACTSS |= 0x0008;         // 13) enable sample sequencer 3
  
	
}









//------------ADC0_InSeq3------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
unsigned long ADC0_InSeq3(void){  
	unsigned long result;
  ADC0->PSSI = 0x0008;            // 1) initiate SS3
  while((ADC0->RIS&0x08)==0){};   // 2) wait for conversion done
  result = ADC0->SSFIFO3&0xFFF;   // 3) read result
  ADC0->ISC = 0x0008;             // 4) acknowledge completion
  return result;
}


