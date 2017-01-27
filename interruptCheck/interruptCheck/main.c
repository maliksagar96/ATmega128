/*
 * interruptCheck.c
 *
 * Created: 09-02-2016 17:42:33
 * Author : sagar
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART_128.h"
	
int a = 0;	
volatile int n = 1;
	
int main(void) {

    USART_Init(12,1);
	EIMSK = 0b11110011;
	EICRA |= 0xff;
	EICRB |= 0xff;
	sei();
 
	while (1) {
	
  	USART_TransmitNumber(1,n);
	
	}
}

/*
ISR(INT0_vect) {	a++;
USART_TransmitNumber(a,1);
USART_Transmitchar(0x0D,1);
}
*/

ISR(INT1_vect) {
	a++;
USART_TransmitNumber(a,n);
USART_Transmitchar(0x0D,n);

}
/*
ISR(INT2_vect) {
	a++;
USART_TransmitNumber(a,1);
USART_Transmitchar(0x0D,1);

}

ISR(INT3_vect) {
		a++;
USART_TransmitNumber(a,1);
USART_Transmitchar(0x0D,1);
}

ISR(INT4_vect) {
	a++;
USART_TransmitNumber(a,1);
USART_Transmitchar(0x0D,1);
}

ISR(INT5_vect) {
	a++;
	USART_TransmitNumber(a,1);
	USART_Transmitchar(0x0D,1);
}
*//*
ISR(INT6_vect) {	a++;
	USART_TransmitNumber(a,1);
	USART_Transmitchar(0x0D,1);
}
*/
/*
ISR(INT7_vect) {	a++;
	USART_TransmitNumber(a,1);
	USART_Transmitchar(0x0D,1);
}
*/




