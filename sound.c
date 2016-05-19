


#include "sound.h"

int music [5] = { 0x666666 , 0x066666 , 0x026666 ,0x006666 ,  0x006000} ;

int counter = 0 ;
int temp = 0 ;
int turn  = 3 ;
char function = 'w' ;

void set_counter(int c )
{
	counter = c;

}
int get_counter(void)
{
	
return counter;
}

char get_func(void)
{
return function;
}


// input from PA3, output from PA2, SysTick interrupts
void Sound_Init(void){ 
	volatile unsigned long delay;
  SYSCTL->RCGC2 |= 0x00000002;      // 1) B clock
  delay = SYSCTL->RCGC2;            // delay to allow clock to stabilize 	
  GPIOB->AMSEL &= 0x00;        // 2) disable analog function
  GPIOB->PCTL &= 0x0000000 ;   // 3) GPIO clear bit PCTL  
  GPIOB->DIR |=  ( 1 << 2 ) ;          // 4.2) PB2 output  
  GPIOB->AFSEL &= 0x00;        // 5) no alternate function
  GPIOB->PUR = 0x00;         	 // 6) disable pullup resistor on PE0       
  GPIOB->DEN |= 0x0F;          // 7) enable digital pins PE4-PE0
	
	SysTick->CTRL  = 0;                   // disable SysTick during setup
  SysTick->LOAD = music[turn++];        // maximum reload value
  SysTick->VAL = 0;                // any write to current clears it             
  //SysTick->CTRL = 0x00000007;          // enable SysTick with core clock
	
	
}

		
		// 1 enemy body killed
		// 2 bomb sent
		// 3 you hit

void enemy_sound(void)
{
	
		function = 'y';
		SysTick->CTRL  = 0;                   // disable SysTick during setup
		SysTick->LOAD = music[1];        // maximum reload value
		SysTick->VAL = 0;                // any write to current clears it             
		SysTick->CTRL = 0x00000007;          // enable SysTick with core clock
		
		if( temp == 100 )
			stop_sound();
		
		temp++;
}




void bomb_sound(void)
{
		function = 'b' ;
		SysTick->CTRL  = 0;                   // disable SysTick during setup
		SysTick->LOAD = music[2];        // maximum reload value
		SysTick->VAL = 0;                // any write to current clears it             
		SysTick->CTRL = 0x00000007;          // enable SysTick with core clock
		
		if( temp == 100 )
			stop_sound();
		
		temp++;
}







void bomber_sound(void)
{
		function = 'r';
		SysTick->CTRL  = 0;                   // disable SysTick during setup
		SysTick->LOAD = music[3];        // maximum reload value
		SysTick->VAL = 0;                // any write to current clears it             
		SysTick->CTRL = 0x00000007;          // enable SysTick with core clock
		
		if( temp == 100 )
			stop_sound();
		
		temp++;
}


void start_sound(void)
{
		
		function = 'w' ;
		SysTick->CTRL = 0x00000007;          // enable SysTick with core clock
		
		if( temp == 1000 )
		{	
		temp = 0 ;	
		SysTick->CTRL  = 0;                   // disable SysTick during setup
		
		if(turn == 3 )
		turn = 4 ;
		else if ( turn == 4)
		turn = 2 ;	
		else 
		turn = 3		;
		
		SysTick->LOAD = music[turn];        // maximum reload value
		SysTick->VAL = 0;                // any write to current clears it             
		SysTick->CTRL = 0x00000007;          // enable SysTick with core clock
			
		}

		temp++ ;
}


void stop_sound(void )
{
		SysTick->CTRL  = 0;                   // disable SysTick during setup
		GPIOB->DATA = 0x00;
		temp = 0;
}

void resume_sound(void )
{
		SysTick->CTRL = 0x00000007;          // enable SysTick with core clock
	
}


void end_sound(void)
{
	function = 'd';
	SysTick->CTRL = 0x00000007;          // enable SysTick with core clock
		if( temp == 1000 )
		{	
		temp = 0 ;	
		SysTick->CTRL  = 0;                   // disable SysTick during setup
		
		if(turn == 3 )
		turn = 4 ;
		else 
		turn = 3		;
		
		SysTick->LOAD = music[turn];        // maximum reload value
		SysTick->VAL = 0;                // any write to current clears it             
		SysTick->CTRL = 0x00000007;          // enable SysTick with core clock
			
		}
		
		temp++ ;
}



// called at 880 Hz

