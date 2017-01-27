/*
 * pot_motor_test2.c
 *
 * Created: 07-10-2016 02:39:28
 * Author : sagar
 */ 

#include <avr/io.h>

int a;

void initialize_ADC(void)
{
	ADMUX |=(1<<REFS0);//avcc is reference
	ADMUX &=~((1<<MUX1)|(1<<MUX2)|(1<<MUX3)|(1<<MUX4));//set adc1
	ADMUX |= (1<<MUX0);
	ADCSRA |=(1<<ADEN);//ADC enable
	ADCSRA |=(1<<ADPS2)|(1<<ADPS1);//ADC prescaler is 64
//	ADCSRA |=(1<<ADIE);//ADC conversion complete interrupt enable
}
void initialize_PWM(void)
{
	TCCR1A |= (1<<WGM11);//set fast pwm
	TCCR1B |=(1<<WGM12)|(1<<WGM13);
	TCCR1A |= (1<<COM1A1)|(1<<COM1A0);//inverting mode
	TCCR1B |=(1<<CS10);//clk start with no prescaling
	ICR1 = 65535;
	
	TCNT1 = 0;
}
void compute_motor_speed(int ADC_value)
{
	OCR1A =65535-(int)((65535*ADC_value)/1023);
    TCNT1 = 0;
}
int main(void)
{
	DDRB |= (1<<PINB5);
	initialize_ADC();
	initialize_PWM();
	ADCSRA |=(1<<ADSC);
	while (1)
	{
		while(ADCSR &(1<<ADSC));
		compute_motor_speed(ADC);
		ADCSRA|=(1<<ADSC);
	}

}


