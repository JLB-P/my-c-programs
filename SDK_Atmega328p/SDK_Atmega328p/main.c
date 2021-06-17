/*
 * SDK_Atmega328p.c
 *
 * Created: 6/16/2021 10:37:49 AM
 * Author : jlb
 */ 

#include <avr/io.h>
#include "io_ports.h"
#include "leds.h"


int main(void)
{
    /* Replace with your application code */
	init_ports();
    while (1) 
    {
		led_on_off();
    }
}

