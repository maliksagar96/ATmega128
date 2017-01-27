/*
 * Clower_piston.c
 *
 * Created: 22-01-2011 01:38:03
 *  Author: Drishti
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

void DELAY(int delay)
{
	while(delay--)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	DDRA&=~((1<<PA0)|(1<<PA1));
	PORTA|=(1<<PA0)|(1<<PA1);
	DDRC|=(1<<PC0)|(1<<PC1);
	int i=0, j=0, clear1_flag=0, clear2_flag=0;
//    PORTC|=(1<<PC0)|(1<<PC1);
	PORTC|=(1<<PC0);
	_delay_ms(100);
	PORTC&=~(1<<PC0);
	while(1)
	{
		
		if(bit_is_clear(PINA,0) && clear1_flag==0)
		{
			//PORTC&=~(1<<PC0);
			PORTC|=(1<<PC1);
			_delay_ms(100);
			PORTC&=~(1<<PC1);
			_delay_ms(1000);
			PORTC=0;
			PORTC|=(1<<PC0);
			_delay_ms(100);
			PORTC&=~(1<<PC0);
			clear1_flag=1;
		}
		if(bit_is_clear(PINA,1) && clear2_flag==0)
		{
			
			PORTC|=(1<<PC1);
			_delay_ms(100);
			PORTC&=~(1<<PC1);
			_delay_ms(1000);
			PORTC|=(1<<PC0);
			_delay_ms(100);
			PORTC&=~(1<<PC0);
			clear2_flag=1;
		}
	}
}
