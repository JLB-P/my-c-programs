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
	
	// Define puerto D-->salida
	DDRD = 0xff;
	//LCD de prueba a 4 bits
	/*	Puerto D -> LCD
		PD0			RS
		PD1			RW
		PD2			E
		PD3			D4
		PD4			D5
		PD5			D6
		PD6			D7
	*/
} 