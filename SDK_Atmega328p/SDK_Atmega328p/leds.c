/*
 * leds.c
 *
 * Created: 6/17/2021 6:48:59 AM
 *  Author: jlb
 */ 
#define F_CPU 16000000UL 
#include <avr/io.h>
#include <util/delay.h>
void led_on_off (void)
{
	PORTB ^= 1 << PB5; //toggle led
	_delay_ms(100);
}