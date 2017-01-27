/*
 * sokhyoku.c
 *
 * Created: 12/9/2016 5:03:23 PM
 *  Author: RahulGunkar
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART_128.h"  

#define motor_port		DDRC
#define dir_port		PORTC
#define pwm_port		DDRB
#define pwm_pins		PORTB
#define PWM_max			65535
#define pwmDivisor		10

volatile int diskCount[4] = {0,0,0,0};
enum{all};					//for rotating all motors at the same time, all = 0
volatile int dirPin[4][3];
volatile int maxPWM[4] = {0,PWM_max/pwmDivisor,PWM_max/pwmDivisor,PWM_max/pwmDivisor};

void pwmInit() {

		pwm_port = 0xFF;
		motor_port = 0xFF;
	
		TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<COM1C1) | (1<<WGM11) ;
		TCCR1B |= (1<<CS10) | (1<< WGM13) | (1<<WGM12);

		PORTC = 0x00;
		ICR1 = 65535;
	
		dirPin[1][1] = 0;
		dirPin[1][2] = 1;
		dirPin[2][1] = 2;
		dirPin[2][2] = 3;
		dirPin[3][1] = 4;
		dirPin[3][2] = 5;

}

void initinterrupt ()
{
	EICRA |= (1<<ISC01) | (1 << ISC11) | (1 << ISC21);
	EICRB = (1 << ISC71) | (1 << ISC61) | (1 << ISC51);
	EIMSK = (1<<INT5) | (1 << INT6) | (1 << INT7);
}
/*
void interrupt_check() {
	
	USART_TransmitNumber(diskCount,0);
}
*/
void stop_motors(int n) {
	

	if(n == 1) {
		OCR1A = 0;
		motor_port |= (1 << dirPin[1][1]) | (1 << dirPin[1][2]);
	}
	else if(n == 2) {
		OCR1B = 0;
		motor_port |= (1 << dirPin[2][1])|(1 << dirPin[2][2]);
	}
	else if(n == 3) {
		OCR1C = 0;
		motor_port |= (1 << dirPin[3][1])|(1 << dirPin[3][2]);
	}
	
			
}


void rotateMotor(int n) {
	
	if(n == all) {
		OCR1A = maxPWM[1] ;
		OCR1B = maxPWM[2];
		OCR1C = maxPWM[3];
		dir_port = 0;
		dir_port |= (1 << dirPin[1][1]) | (1 << dirPin[2][1]) | (1 << dirPin[3][1]);
 		return;
	}
	
	else if(n == 1) {
		OCR1A = maxPWM[1];
		dir_port = 0;
		dir_port |= (1 << dirPin[1][1]);
	    return;
	}	
	
	else if(n == 2) {
		OCR1B = maxPWM[2];
		dir_port = 0;
		dir_port |= (1 << dirPin[2][1]);
		return;
	}
	
	else if(n == 3) {
		OCR1C = maxPWM[3];
		dir_port = 0;
		dir_port |= (1 << dirPin[3][1]);
		return;
	}
}

void motorCheck(int n) {
	
	int data = n & 7;
	rotateMotor(data);
}

int main(void)
{
	pwmInit();
	initinterrupt();
	USART_Init(12,0);
	rotateMotor(all);
	sei();

		while (1) {
	//rotateMotor(all);
		}	
}

ISR(INT5_vect) {
	diskCount[1]++;
	if(diskCount[1] ==1){
		stop_motors(1);
	}
}

ISR(INT6_vect) {
	diskCount[2]++;
	if(diskCount[2] == 1){
	stop_motors(2);
	}
}

ISR(INT7_vect) {
	diskCount[3]++;
	if(diskCount[3] == 1){
		stop_motors(3);
	}	
}