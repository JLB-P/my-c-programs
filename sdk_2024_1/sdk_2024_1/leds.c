/*
 * leds.c
 *
 * Created: 9/20/2023 4:18:02 PM
 *  Author: josel
 */ 
#include <avr/io.h>
#include <avr/delay.h>

void led_on_off(void)
{
	for(int i = 0; i < 5; i++)
	{
		PORTB &= 0 << PB5;
		_delay_ms(5000);
		PORTB |= 1 << PB5;
		_delay_ms(5000);	
	}
}
void led_on(void)
{
	PORTB |= 1 << PB5;
}
void led_off(void)
{
	PORTB &= 0 << PB5;
}

