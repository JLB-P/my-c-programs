/*
 * sdk_2024_1.c
 *
 * Created: 9/20/2023 4:14:08 PM
 * Author : josel
 */ 

#include <avr/io.h>
#include "ports.h"
#include "leds.h"

int main(void)
{
    /* Replace with your application code */
	init_ports();
	led_on_off();
    while (1) 
    {
		
    }
}

