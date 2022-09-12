/*
 * SDK_2023_1.c
 *
 * Created: 9/5/2022 5:19:12 PM
 * Author : josel
 */ 

#include <avr/io.h>
#include "ports.h"
#include "leds.h"

int main(void)
{
	init_ports();
	
    /* Replace with your application code */
    while (1) 
    {
		led_on_off();
    }
}

