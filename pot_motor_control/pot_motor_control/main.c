/*
 * pot_motor_control.c
 *
 * Created: 07-10-2016 02:11:49
 * Author : sagar
 */ 

#include <avr/io.h>



void initialize_ADC(void)
{
	ADMUX |=(1<<REFS0);//avcc is reference
	ADMUX &=~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3)|(1<<MUX4));//set adc0
	ADCSRA |=(1<<ADEN);//ADC enable
	ADCSRA |=(1<<ADPS2)|(1<<ADPS1);//ADC prescaler is 64
	ADCSRA |=(1<<ADIE);//ADC conversion complete interrupt enable
}
void initialize_PWM(void)
{
	TCCR0 |= (1<<WGM01)|(1<<WGM00);//set fast pwm
	TCCR0 |= (1<<COM01)|(1<<COM00);//inverting mode
	TCCR0 |=(1<<CS00);//clk start with no prescaling
	TCNT0 =0;
	OCR0 =255;
}
void compute_motor_speed(int ADC_value)
{
	TCNT0 =0;
	OCR0 =255-(int)((255*ADC_value)/1023);
}
int main(void)
{
DDRB |= (1<<PINB4);
initialize_ADC();
initialize_PWM();
ADCSRA |=(1<<ADSC);
while (1)
{
	
}

}

ISR(ADC_vect)
{
	compute_motor_speed(ADC);
	ADCSRA|=(1<<ADSC);
}