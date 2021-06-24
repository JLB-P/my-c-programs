/*
 * io_ports.c
 *
 * Created: 6/17/2021 6:48:03 AM
 *  Author: jlb
 */ 
#include <avr/io.h>
void init_ports (void)
{
	// Define puerto B-->salida
	DDRB = 0xff;
	/*LCD de prueba a 4 bits
		Atmega328p  
		PB0			RS
		PB1			RW
		PB2			E
		PB4			D4
		PB5			D5
		PB6			D6
		PB7			D7
	*/
	//Port B definition
	//DDRB |= 1 << PB5; //arduino led on pb5
}