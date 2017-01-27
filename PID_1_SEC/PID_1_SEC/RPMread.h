#ifndef RPMread
#define RPMread

#include <avr/io.h>
#include <avr/interrupt.h>
#define prescaler 1	//Define Prescaler for Timer. Default is 1.

volatile float tick=0;
volatile int dir,sig=0,interruptpin,total=0,i,movingarray[100],average_length,timer;
volatile unsigned long CPUf;
//Function initializes the modes for reading RPM
//Pin is the external interrupt pin numbers; options are INT0,INT1 or 2 means both INT1 and INT0.
//timer_Value must be 0,1 or 2. 0 is TCNT0, 1 is TCNT1, 2 is TCNT2
//average_length specifies the number of readings to perform moving average on.
void RPMinit(int pin,int timer_Value,int averagelength,unsigned long CPU)
{
	interruptpin=pin;
	CPUf=CPU;
	average_length=averagelength;
	if(timer_Value==0)
	{
		TCCR0 = 1<<CS00;
		timer=0;
	}
	else if(timer_Value==1)
	{
		TCCR1B = 1<<CS10;
		timer=1;
	}
	else if(timer_Value==2)
	{
		TCCR2 = 1<<CS20;
		timer=2;
	}
	
	//Setting Up  ExternalInterrupt
	if(interruptpin==6)
	{
		GICR = 1<<INT0;
		MCUCR = 1<<ISC01 | 1<<ISC00;
	}
	else if(interruptpin==7)
	{
		GICR = 1<<INT1;		
		MCUCR = 1<<ISC10 | 1<<ISC11;
	}
	else if(interruptpin==2)
	{
		GICR = 1<<INT0 | 1<<INT1;
		MCUCR = 1<<ISC10 | (1<<ISC11) | (1<<ISC00) | (ISC01);
	}
	sei();
	
	total=0;
	for(i=0;i<average_length;i++)
	{
		movingarray[i]=0;
	}
}


//Function to read RPM using Timer and External Interrupt pin "pin".
//ticksPerRound is the ticks per revolution of encoder.
//CPU is the F_CPU
//max is the sample value of TCNTn.
int readRPM(int ticksPerRound,unsigned int max)
{
	int avg=0;
	DDRB &= ~(1<<PINB0);
	PORTB &= ~(1<<PINB0);
	total-=movingarray[0];
	for(i=0;i<average_length-1;i++)
	{
		movingarray[i]=movingarray[i+1];
	}
	
	tick=0;
	if(timer==0)
	{
		TCNT0=0;
		while(TCNT0<max);
	}
	else if(timer==2)
	{
		TCNT2=0;
		while(TCNT2<max);
	}
	else if(timer==1)
	{
		TCNT1=0;
		while(TCNT1<max);
	}
	
	movingarray[average_length-1] = (tick / ticksPerRound) * CPUf * 60.0 / (max * prescaler);
	
	total+=movingarray[average_length-1];
	avg=total/average_length;
	return avg;
}

int get_ticks_per_round(unsigned int max)
{
	if(timer==0)
	{
		TCNT0=0;
		while(TCNT0<max);
	}
	else if(timer==2)
	{
		TCNT2=0;
		while(TCNT2<max);
	}
	else if(timer==1)
	{
		TCNT1=0;
		while(TCNT1<max);
	}
	return tick;
}

int direction()
{
	return dir;
}

ISR(INT0_vect)
{
	tick++;
	if(bit_is_set(PINB,PINB0))
	{
		dir=1;
	}
	else dir=-1;
}
#endif