/*
 * leds.c
 *
 * Created: 9/7/2022 4:40:35 PM
 *  Author: josel
 */ 
#include <avr/io.h>
#include <avr/delay.h>

void led_on_off(void)
{
	PORTB &= 0 << PB5;
	_delay_ms(100);
	PORTB |= 1 << PB5;
	_delay_ms(100);
}