/*
 * leds.c
 *
 * Created: 6/17/2021 6:48:59 AM
 *  Author: jlb
 */ 
#define F_CPU 16000000UL //arduino freq.
#include <avr/io.h>
#include <util/delay.h>

void power_on (void)
{
	int i;
	
	for (i = 0;i < 5;i++)
	{
		PORTB ^= 1 << PB5; //toggle led
		_delay_ms(100);
	}
}