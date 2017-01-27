#ifndef external_INT
#define external_INT


#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

enum{rising,falling,levelChange};
	/* interrupt 0,1,2,3 can call only rising and falling edge...interrupt 4,5,6,7 can trigger rising,falling.level change.*/
void setInterrupt(int ,int );

#endif
