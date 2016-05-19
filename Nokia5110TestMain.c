// Nokia5110TestMain.c
// Runs on LM4F120/TM4C123
// Test the functions in Nokia5110.c by printing various
// things to the LCD.
// Daniel Valvano
// September 16, 2013

// Font table, initialization, and other functions based
// off of Nokia_5110_Example from Spark Fun:
// 7-17-2011
// Spark Fun Electronics 2011
// Nathan Seidle
// http://dlnmh9ip6v2uc.cloudfront.net/datasheets/LCD/Monochrome/Nokia_5110_Example.pde

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected
// Ground        (Gnd, pin 8) ground

// Red SparkFun Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// SSI0Fss       (SCE, pin 3) connected to PA3
// Reset         (RST, pin 4) connected to PA7
// Data/Command  (D/C, pin 5) connected to PA6
// SSI0Tx        (DN,  pin 6) connected to PA5
// SSI0Clk       (SCLK, pin 7) connected to PA2
// back light    (LED, pin 8) not connected

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "PLL.h"
#include "drawings.h"
#include "porte.h"
#include "ADC.h"
#include "sound.h"


// delay function for testing from sysctl.c
// which delays 3*ulCount cycles
#ifdef __TI_COMPILER_VERSION__
	//Code Composer Studio Code
	void Delay(uint32_t ulCount){
	__asm (	"    subs    r0, #1\n"
			"    bne     Delay\n"
			"    bx      lr\n");
}

#else
	//Keil uVision Code
	__asm void
	Delay(uint32_t ulCount)
	{
    subs    r0, #1
    bne     Delay
    bx      lr
	}
#endif

	
  
	
	
volatile  long ADCvalue = 0 , oldValue = 0 ;	
char lock = 0 ;
int test [20];
int in = 0;

	
	
	
void SysTick_Handler(void){

	int c = get_counter();
		
	
	if(c)
		GPIOB->DATA ^=  ( 1 << 2 ) ;
		else 
		GPIOB->DATA = 0x00;
	
		set_counter(c ^ 0x01);
		
		
		switch(get_func())
		{	
			case 'w':
				start_sound();
				break;
			case 'd':
				end_sound();
				break;
			case 'r':
				bomber_sound();
				break;	
			case 'b':
				bomb_sound();
				break;	
			case 'y':
				enemy_sound();
				break;
		}		
	}
		
// Subroutine Defines interrupt on portE
// Inputs:  none
// Outputs: LEDs lit up
// Notes:   friendly means it does not affect other bits in the port
void GPIOPortE_Handler(void)
{
				interrupt_ackn();
			
				
				if( ( GPIOE->DATA & 0x01) == 0)
				shoot();
				
				if ( ( GPIOE->DATA & 0x10) == 0)
				{ 
				lock ^= 1 ;
				if (lock)
				pauser();
				}
				
				Delay1ms(30);	
}







int main(void){
  
	int i ;
	uint32_t score = 0;
	uint32_t count = 0;
  
	PortE_Init();
	init_interrupt();
	Sound_Init();       
	PLL_Init();                           // set system clock to 50 MHz
  ADC0_InitSWTriggerSeq3_Ch1();         // ADC initialization PE2/AIN1	
	Nokia5110_Init();
	
	start_sound();
	welcomer();
	ADCvalue = ADC0_InSeq3() ;
	start_pos(ADCvalue);
  oldValue = ADCvalue;
	stop_sound();


	while(1){
   
		
				if(!lock)
					{
		
						ADCvalue = ADC0_InSeq3() ;
							
						  score += check_death();
							update_diaplay();
							update_pos(oldValue , ADCvalue);
							oldValue = ADCvalue;
							score++;
					}	
			
	
					if (getLive() == 0)
						break;					
				}
			
			end_sound();
			gameOver(score / 10);			
				while(1) ;
	
}



		/*
		Nokia5110_SetCursor(5, 5);          // five leading spaces, bottom row
    Nokia5110_OutChar((count%26)+'A');
    Nokia5110_OutChar(' ');
    Nokia5110_OutUDec(count);
    Delay(8333333);                     // delay ~0.5 sec at 50 MHz
    count = count + 1;
  
	*/
