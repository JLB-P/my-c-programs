/*
 * m328p_ACRobot.c
 *
 * Created: 24/11/2021 06:40:00 p. m.
 * Author : jlb
 */ 

#include <avr/io.h>
#include "io_ports.h"
#include "leds.h"
#include "motors.h"

int main(void)
{
	init_ports();
	power_on();
	init_timer1();
	example_motors();
    while (1) 
    {
    }
}