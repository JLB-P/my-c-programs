/*
 * LEDs.c
 *
 * Created: 01/03/2016 07:10:12 p. m.
 *  Author: JLB
 */ 

#include <avr/io.h>
#include <util/delay.h>

void Power_on (void)
{
		PORTB ^= 1<<PB5; //Enciende LED (con 0's)
		_delay_ms(200);
}