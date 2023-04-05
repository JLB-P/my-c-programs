/*
 * leds.c
 *
 * Created: 6/17/2021 6:48:59 AM
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <util/delay.h>

void power_on (void)
{
	int i;
	for (i = 0;i < 6;i++)
	{
		PORTB ^= 1 << PB5; //Led off
		_delay_ms(100);
	}
}