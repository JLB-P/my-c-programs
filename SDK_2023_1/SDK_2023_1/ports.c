/*
 * ports.c
 *
 * Created: 9/5/2022 5:24:31 PM
 *  Author: josel
 */ 
#include <avr/io.h>

void init_ports(void)
{
	//LED Power on
	DDRB |= 1 << PB5;
	PORTB |= 1 << PB5;
} 