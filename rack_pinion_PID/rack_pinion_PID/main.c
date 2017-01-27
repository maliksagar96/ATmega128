#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include "USART_128.h"

#define kp						100
#define ki						0.01
#define kd						0.00001

#define constantDistance		30			//in cm

volatile uint8_t adcConvData = 0;

float E = 0,e_old = 0;

void delay_ms(int i) {
	while (i--)
	_delay_ms(1);
}

float PID(float e) {
	
	float pid;
	pid = kp*e + ki*E + kd * (e - e_old);
	E += e;
	e_old = e;
	return pid;
	
}

void motionOfMotor(float pid) {
	if(pid > ICR1) {
		pid = ICR1;
		
	}
	else if(pid < 0) {
		
 		pid = 0;
// 		pid = -pid;		
	}
	OCR1A = pid;
}

void init() {
	
	DDRB = 0xFF;
	DDRC =0xFF;							//for direction pins
	
	USART_Init(12,0);
	sei();
	//setting up pwm commands
	TCCR1A |= 1<<COM1A1 | 1<<COM1B1 | 1<<COM1C1 | 1<<WGM11 ;
	TCCR1B |= 1<<CS10 | 1<< WGM13 | 1<<WGM12;
	ICR1 = 65535/15;
	

	//adc commands
	ADCSRA |= (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1);
	ADMUX|=(1<<REFS0)|(1<<REFS1)|(1<<ADLAR);
	ADCSRA |= (1<<ADSC);
}



int main(void) {
	init();
	float error = 0;
	PORTC = 0b00000010;
	while(1) {
		
		float cm = 1/ (0.00046 * adcConvData);
		
		error = cm - constantDistance;
		
		
		if(error < -5) {
			PORTC = 0b00000001;
		}	else if(error > 5) {
			PORTC = 0b00000010;
		}
		
		
		
		delay_ms(10);
 		
		
		if(error < 5  && error > -5) {
			OCR1A = 0;
			}   else   {
			motionOfMotor(PID(error));
		}
		
		USART_TransmitNumber(error,0);
		USART_Transmitchar(' ',0);
		USART_TransmitNumber(cm,0);
		USART_Transmitchar(' ',0);
		USART_TransmitNumber(OCR1A,0);
		USART_Transmitchar(0x0d,0);
	}
}

ISR(ADC_vect) {
	adcConvData = ADCH;
	ADCSRA |=(1<<ADSC);
}
