/*
 * RPM_ANIKET.c
 *
 * Created: 25-11-2015 15:48:10
 * Author : sagar
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "RPMread.h"
#include "USART_32.h"
#define kp 0.05
#define ki 0.0000015
#define kd 0.0000001
#define req_rpm 200
volatile float rpm;
//volatile float e;
volatile long overFlow;
float PID(float e);
volatile float e_old = 0,E = 0;
int main(void)
{
	USART_Init(12);
    RPMinit(6,1,10,8000000);
	DDRB |= 1<<PINB3;
	TCCR0 |= 1<<WGM01 | 1<<WGM00 | 1<<COM01 | 1<<CS00; 
	TIMSK |= 1<<TOIE0;
	TIFR |= 1<<TOV0;	
	sei();
	float e;
    while (1) 
    {
		if(overFlow == 31372)
		{	
			rpm = readRPM(2000,60000);
			e = req_rpm - rpm;
	//  		if(e<0)
	//  		{
	//  			USART_TransmitNumber(-e);
	//  		}
	// 		else	
	// 		USART_TransmitNumber(e);
	// 		USART_Transmitchar(' ');
			OCR0+=PID(e);
			USART_TransmitNumber(rpm);
			USART_Transmitchar(' ');
	// 		OCR0 += PID(e);
			if(OCR0>255) OCR0 = 255;
			else if(OCR0<0) OCR0 = 0;
		}
	
	}
}
 
float PID(float e)
{
	float pid;
	pid = kp*e + ki*E + kd*(e - e_old);
//     USART_TransmitNumber(pid);
// 	USART_Transmitchar(' ');	
// 	USART_Transmitchar(0x0d);
// 		
//	USART_Transmitchar(0x0d);
	E += e;
	e_old = e;
	return pid;
}

ISR(TIMER0_OVF_vect)
{
	overFlow++;
	if(overFlow > 31372)
	{
		overFlow = 0;
	}
}