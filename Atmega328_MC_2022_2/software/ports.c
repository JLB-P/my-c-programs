/*
 * ports.c
 *
 * Created: 3/15/2022 6:42:47 PM
 *  Author: josel
 */ 
#include <avr/io.h>

void init_ports(void)
{
	//assign pin power-led
	DDRB |= 1 << PINB5;
}