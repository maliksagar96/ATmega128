/*
 * compass_sensor_nterface.c
 *
 * Created: 21-01-2011 00:55:33
 *  Author: Drishti
 */ 

#define F_CPU 8000000UL 

#include <avr/io.h>
#include "compass_sensor.h"
#include "USART_32.h"

int main(void)
{
volatile int degree = 0;
	
init_HMC5883L();
USART_Init(12);

    while(1)
    {
      degree = getHeading();
      USART_TransmitNumber(degree);
      USART_Transmitchar(' ');
      USART_Transmitchar(0x0D);
    }
}