/*
 * GRP_gate.c
 *
 * Created: 19-11-2016 00:37:15
 * Author : sagar
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

#define PWM_pin 3
#define dir1 5
#define	dir2 4
#define switch_pin 1

void init() {
	
	DDRE = 0xff;
	DDRB = 0x00;
}

void open_gate() {
	
	PORTE = (1 << dir1);
	PORTE &=~ (1 << dir2);
	PORTE = (1 << PWM_pin);

	_delay_ms(2000);
	_delay_ms(2000);
	_delay_ms(1000);
	PORTE &=~ (1<<PWM_pin);
		
} 

void close_gate() {

	PORTE = (1 << dir2);
	PORTE &=~ (1 << dir1);
	PORTE = (1 << PWM_pin);
	
	_delay_ms(2000);
	_delay_ms(2000);
	_delay_ms(1000);
	PORTE &=~ (1<<PWM_pin);
	
	
}

int main(void)
{
    /* Replace with your application code */
	
	int test_variable = 1;
	int a = 0; 
	
    while (1) 
    {
	//	a++;
			
		if(test_variable) {
				open_gate();
				_delay_ms(2000);
				_delay_ms(2000);
				_delay_ms(2000);
				_delay_ms(2000);
				_delay_ms(2000);
				close_gate();	
		}
	/*	
		if(a == 2) {
			test_variable = 0;
		}*/
		
    }
}

