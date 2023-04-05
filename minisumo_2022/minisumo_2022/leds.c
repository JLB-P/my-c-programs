/*
 * leds.c
 *
 * Created: 11/22/2022 12:53:55 PM
 *  Author: josel
 */ 
#include <avr/io.h>
#include <util/delay.h>

void power_on (void)
{
	int i;
	for (i = 0;i < 6;i++)
	{
		PORTB ^= 1 << PB5; //Led on/off
		_delay_ms(100);
	}
}