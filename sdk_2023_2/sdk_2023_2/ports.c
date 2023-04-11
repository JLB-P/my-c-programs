/*
 * ports.c
 *
 * Created: 3/7/2023 7:38:55 PM
 *  Author: josel
 */ 
#include <avr/io.h>

void init_ports (void)
{
	//Led poer/on
	DDRB |= 1 << PB5; //Pin 5 -> output
	//test timer on CTC mode
	DDRB |= 1 << PB1; //OC1A -> output
	//test timer on PWM mode
	DDRB |= 1 << PB3; //OC2A -> output
} 