/*
 * PS_2_recieving.c
 *
 * Created: 22-12-2015 14:15:02
 * Author : sagar
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include "USART_128.h"
#include <avr/interrupt.h>

int main(void)
{
	USART_Init(12,0);
	uint8_t v1,v2;
	USART_InterruptEnable(0);
	USART_TransmitString("Up and Running!", 0);
    while (1); 
    {
	 }
}

ISR(USART0_RX_vect) {
	int data = USART_Receive(0);
	USART_Transmitchar(data, 0);
	USART_Transmitchar(0x0d,0);	
//	New_Line(0);
}