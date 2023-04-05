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
	DDRB |= (1 << PINB5);
	// twi outputs
	DDRC|=(1<<PINC4)|(1<<PINC5);	// SDA & SCL outputs
	PORTC|=(1<<PINC4)|(1<<PINC5);	// SDA & SCL pull up activation
	// adc inputs
	DDRC&=(0<<PINC0);				// ADC0 
}