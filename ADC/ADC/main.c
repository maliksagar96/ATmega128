/*
 * ADC.c
 *
 * Created: 27-10-2015 18:21:44
 * Author : sagar
 */ 

#include <avr/io.h>
#include "USART_32.h"
#include <avr/interrupt.h>

int main(void)
{
	ADMUX |= 1<<REFS0 | 1<<MUX0;			//ref of 5v and also connect potentiometer to 
	ADCSRA |= 1<<ADEN;						//adc enable
	
	
	ADCSRA |=1<<ADIE;						//interrupt enable
	TCCR1B |= 1<< WGM12 | 1<<WGM10;			
	TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
	sei();
	ADCSRA |= 1<<ADSC;			
    while (1) 
    {
    }
	
}

ISR(ADC_vect)
{
	uint8_t value = ADCL;
	uint16_t tenBit |= ADCH<<2 | value>>6;
	USART_TransmitNumber(tenBit);
	USART_Transmitchar(0x0d);
	
}
