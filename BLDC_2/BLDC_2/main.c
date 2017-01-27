/*
 * RPM_module.c
 *
 * Created: 16-10-2015 16:38:05
 *  Author: BhaviK
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main() {
		DDRD=0b00110000;
		TCCR1A |= 1<<COM1A1|1<<COM1B1|1<<WGM11;			
		TCCR1B |= 1<<WGM12|1<<WGM13|1<<CS11;			//prescalar of eight
		ICR1=19999;
		
		OCR1A = 1999;
		_delay_ms(5000);
		OCR1A = 999;
		_delay_ms(2000);
		OCR1A = 1999;
    
	
}
