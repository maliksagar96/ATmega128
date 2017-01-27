/*
 * motor_driver_check.c
 *
 * Created: 30-01-2016 03:49:21
 * Author : sagar
 */ 

#include <avr/io.h>

void PWM_init() {
    TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<COM1C1) | (1<<WGM11) ;
	TCCR1B |= (1<<CS10) | (1<< WGM13) | (1<<WGM12);
	ICR1 = 65535;
	DDRC = 0xff;
	DDRA = 0xff;
	DDRB = 0xff;
	PORTA = 0xff;
	PORTC = 0x00;
	OCR1A = 65535/5;
	OCR1B = 65535/5;
}

int main(void)
{
	PWM_init();
    
    while (1) 
    {
    }
}

