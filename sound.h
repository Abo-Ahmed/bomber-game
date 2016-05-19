

#include "tm4c123gh6pm.h"


// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode
int checkSW3(void);
void start_sound(void);
void end_sound(void);
void stop_sound(void );
int get_counter(void);
char get_func(void);
void enemy_sound(void);
void bomb_sound(void);
void bomber_sound(void);
void Sound_Init(void);
void resume_sound(void );
void set_counter(int c);
