/*
 * ports.c
 *
 * Created: 9/20/2023 4:15:38 PM
 *  Author: josel
 */ 
#include <avr/io.h>

void init_ports(void)
{
	DDRB |= 1 << PB5;
}