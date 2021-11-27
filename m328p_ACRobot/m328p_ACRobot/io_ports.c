/*
 * io_ports.c
 *
 * Created: 6/17/2021 6:48:03 AM
 *  Author: jlb
 */ 
#include <avr/io.h>
void init_ports (void)
{
	//Timer
	DDRB |= (1 << PB1); //OC1A enable output for left motor
	DDRB |= (1 << PB2); //OC1B enable output for right motor
	//Motor direction
	DDRB |= (1 << PB3) | (1 << PB4); //left motor
	DDRC |= (1 << PC4) | (1 << PC5); //right motor
	// Power on indicator
	DDRB |= (1 << PB5); //Power on led indicator
}