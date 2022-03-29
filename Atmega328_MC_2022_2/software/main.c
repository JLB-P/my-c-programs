/*
 * Atmega328_MC_2022_2.c
 *
 * Created: 3/15/2022 6:41:58 PM
 * Author : josel
 */ 

#include <avr/io.h>
#include "ports.h"
#include "leds.h"

int main(void)
{
	init_ports();
	power_led_on_off();
    /* Replace with your application code */
    while (1) 
    {
    }
}

