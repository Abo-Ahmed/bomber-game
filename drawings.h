
#include <stdint.h>
#include <stdlib.h>
#include "Nokia5110.h"
#include "sound.h"

void Delay1ms(unsigned long msec);
void merge_object( char object_num  , int   x , int y  ) ;

void update_pos(long oldValue , long ADCvalue);

void update_diaplay(void);
int get_rows(char object);
int get_cols(char object);
void pauser (void) ;

void welcomer(void);
void gameOver(uint32_t score);
void start_pos(long ADCvalue);

void set_life(int l);

void shoot(void);

int check_death(void);


int getLive (void);