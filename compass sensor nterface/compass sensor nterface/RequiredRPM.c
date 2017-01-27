/*
 * RequiredRPM.c
 *
 * Created: 01-07-2015 04:12:14
 *  Author: Admin
 */ 


#include <avr/io.h>
#include "USART_32.h"
#include "RPMread.h"
#define F_CPU 8000000UL
#define r 500

int main(void)
{
	float E=0,e,eold,kp=0.41,ki=0.03,kd=1;
	int x=0,RPM, dir;
	unsigned int u;
	DDRB=0xFF;
	PORTB=0;
	PORTB|=1<<PINB1;
	DDRD &= ~(1<<PIND3);
	PORTD &= ~(1<<PIND3);
	USART_Init(12);
	RPMinit(INT0,1,10,F_CPU);
	TCCR0 |= 1<<CS00 | 1<<COM01 | 1<<WGM01 | 1<<WGM00;
	//eold=0;
	while(1)
	{
		/*e=r-x;
		E+=e;
		u=(kp*e)+(ki*E)+(kd*(eold-e));
		OCR0=u;*/
		OCR0=150;
		dir=direction();//eold=e;
		x=readRPM(2000,60000);
		RPM=x*dir;
		if(dir==(-1))
			USART_Transmitchar('-');
		USART_TransmitNumber(x);
		//USART_Transmitchar(dir);
		USART_Transmitchar(0x0D);
	}
}