/*
 * io_ports.c
 *
 * Created: 6/17/2021 6:48:03 AM
 *  Author: jlb
 */ 
#include <avr/io.h>

void init_ports (void)
{
	//Port B definition
	DDRB |= 1 << PB5; //arduino led on pb5
}