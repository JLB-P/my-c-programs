/*
 * Atmega328_MC_2022_2.c
 *
 * Created: 3/29/2022 6:41:34 PM
 * Author : jlb
 */ 

#include <avr/io.h>
#include "ports.h"
#include "leds.h"
#include "usart.h"

int main(void)
{
	init_ports();
	power_led_on_off();
	init_usart(207);
	usart_transmit_string("Hola Jesus...");
	
	/* Replace with your application code */
	while (1)
	{
	}
}
