/*
 * ADC_Test.c
 *
 * Created: 12-02-2016 01:16:56
 * Author : sagar
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint16_t ADC_Result[7]; 

void ADC_Init()
{
	ADCSRA |=(1<<ADPS2);
	ADMUX |=(1<<REFS0);
	ADCSRA |=(1<<ADIE)|(1<<ADEN);
	sei();
	ADCSRA |=(1<<ADSC);
}

int main(void)
{
	ADC_Init();
    while (1) 
    {
    }
}

ISR(ADC_vect)
{
	uint8_t theLow=ADCL;
	switch(ADMUX)
	{
		case 0b01000000 :
							ADC_Result[0] = (ADCH<<8|theLow);
							ADMUX = 0b01000001;
							break;
		case 0b01000001 :
							ADC_Result[1] = (ADCH<<8|theLow);
							ADMUX = 0b01000010;
							break;
		case 0b01000010 :
							ADC_Result[2] = (ADCH<<8|theLow);
							ADMUX = 0b01000011;
							break;
		case 0b01000011 :
							ADC_Result[3] = (ADCH<<8|theLow);
							ADMUX = 0b01000100;
							break;
		case 0b01000100 :
							ADC_Result[4] = (ADCH<<8|theLow);
							ADMUX = 0b01000101;
							break;
		case 0b01000101 :
							ADC_Result[5] = (ADCH<<8|theLow);
							ADMUX = 0b01000110;
							break;
		case 0b01000110 :
							ADC_Result[6] = (ADCH<<8|theLow);
							ADMUX = 0b01000111;
							break;
		case 0b01000111 :
							ADC_Result[7] = (ADCH<<8|theLow);
							ADMUX = 0b01000000;
							break;
	}
	ADCSRA |=(1<<ADSC);
}
