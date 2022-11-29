/*
 * minisumo_2022.c
 *
 * Created: 11/22/2022 12:07:01 PM
 * Author : josel
 */ 

#include <avr/io.h>
#include "ports.h"
#include "leds.h"
#include "motors.h"

int main(void)
{
    init_ports();	//initialize needed system ports
	power_on();		//program running led indicator
	//using motors
	init_timer1();
	motor_left(motor_forward,50);
	//motor_right(motor_forward,100);
	//using us_sensor
// 	init_ext_int0();
// 	init_timer0();
// 	example_sonar();
	while (1) 
    {
    }
}

