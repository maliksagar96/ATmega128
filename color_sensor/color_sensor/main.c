#include <avr/io.h>
#define F_CPU 8000000UL

#include <util/delay.h>
#include "USART_128.h"
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
/*
uint32_t TCSMeasure()
{
	//If the function is entered when the level on OUT line was low
	//Then wait for it to become high.
	if(bit_is_clear(PINA,PA1))
	{
		while(bit_is_clear(PINA,PA1));   //Wait for rising edge
	}


	while(bit_is_set(PINA,PA1));   //Wait for falling edge

	TCNT1=0x0000;//Reset Counter

	TCCR1B=(1<<CS10); //Prescaler = F_CPU/1 (Start Counting)

	while(bit_is_clear(PINA,PA1));   //Wait for rising edge

	//Stop Timer
	TCCR1B=0x00;

	return ((float)4000000UL/TCNT1);

}

void colour_detect1(uint32_t r)
{
	if(r>1000  && r<2000 )
	{
	USART_TransmitString("red",0);	
	USART_Transmitchar(' ',0);
	}
	else if(r>2000 && r<3000)
	{
	USART_TransmitString("blue",0);	
		USART_Transmitchar(' ',0);
	}
	else if(r>3000 && r<4000 )
	{
	USART_TransmitString("green",0);	
		USART_Transmitchar(' ',0);
	}
	else if(r>4000 && r<5000 )
	{
		USART_TransmitString("light_blue",0);
		USART_Transmitchar(' ',0);
	}
	else if(r>5000 && r<6000 )
	{
		USART_TransmitString("yellow",0);
		USART_Transmitchar(' ',0);
	}
	else 
	USART_TransmitString("no_colour",0);
}

void sensor_init()
{
	DDRC=0xFF;
	PORTC=0x0F;
	DDRA|=(1<<PA0);
	//	DDRD|=(1<<PD0);
	DDRA&=~(1<<PA1);
	//DDRA|=(1<<PA0);
	
	//USART_TransmitNumber(11);
	PORTA|=(1<<PA1);
	//PORTD|=(1<<PDO);
}


*/

int main(void)
{
	//sensor_init();
	
	USART_Init(12,1);
	
	
	while(1)
	{
		USART_TransmitNumber(100,1);
		//USART_Transmitchar(0x0D,0);
		/*uint32_t r;

		_delay_ms(10);
		r=TCSMeasure();
		
		_delay_ms(10);
		r+=TCSMeasure();

		_delay_ms(10);
		r+=TCSMeasure();
				
		USART_TransmitNumber(((float)r/3.3),0);
			USART_Transmitchar(' ',0);
		_delay_ms(200);
		colour_detect1(r); 
		New_Line(0);
		
		*/

	}

}