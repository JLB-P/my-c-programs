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
	/*Port B definition
		PB0			
		PB1			
		PB2			
		PB4			
		PB5			Power on LED
		PB6			
		PB7			
	*/
	DDRD &= 0 << PD2; //entrada de interrupci[on externa
	PORTD |= 1 << PD2; //activa resistencia de PullUp.
	
	// Salidas para interfaz a 2 hilos TWI
	DDRC|=(1<<PC4)|(1<<PC5);	// Como salida SDA y SCL
	PORTC|=(1<<PC4)|(1<<PC5);	// SDA y SCL con pull up.
}