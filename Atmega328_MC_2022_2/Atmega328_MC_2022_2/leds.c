/*
 * leds.c
 *
 * Created: 3/15/2022 6:51:11 PM
 *  Author: josel
 */
#include <avr/io.h>
#include <util/delay.h>
 
void power_led_on_off(int i)
{
	for (i = 0; i < 6; ++i)
	{
		PORTB ^= 1 << PINB5; //toggle
		_delay_ms(100);	
	}
	
}

void led_on(char color)
{
	switch (color)
	{
		case 'R':
			PORTB &= 0 << PINB0;
			PORTB |= 1 << PINB1;
			PORTB |= 1 << PINB2;	
			break;
		case 'V':
			PORTB &= 0 << PINB1;
			PORTB |= 1 << PINB0;
			PORTB |= 1 << PINB2;
			break;
		case 'A':
			PORTB &= 0 << PINB2;
			PORTB |= 1 << PINB0;
			PORTB |= 1 << PINB1;
			break;
		default:
		;
	}
}