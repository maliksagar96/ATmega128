/*
 * PS2_INTERFACING.c
 *
 * Created: 21-12-2015 22:37:41
 * Author : sagar
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include "USART_32.h"
#include "PS2.h"

#define maxRPM 500

enum {select, leftStick, rightStick, start, up, right, down, left}; //3rd byte
enum {leftFront2, rightFront2, leftFront1, rightFront11, triangle_up, circle_right, cross_down, square_left}; // 4th byte

int isPressed(uint8_t dataByte, uint8_t dataBit) {
	return ((dataByte & (1 << dataBit)) ? 1 : 0);
}

int main(void) {
	USART_Init(12);
	USART_TransmitString("Up and running");
	init_PS2();
	uint8_t x,y;
    while (1) {
		scan_PS2();
 		_delay_ms(1);
		 
		x =~ data_array[3];
		y =~ data_array[4];		
	//	USART_Transmitchar(0xFF);
		
		if(isPressed(x, up)) {
			USART_TransmitNumber(600);
		} else if(isPressed(x, down)) {
			USART_TransmitNumber(600);
		} else if(isPressed(x, right)) {
			USART_Transmitchar('r');
		} else if(isPressed(x, left)) {
			USART_Transmitchar('l');
		}
		else
		{
			USART_Transmitchar('l');
			
		}
 
 	}
}


