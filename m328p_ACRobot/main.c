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
#include "usart.h"
#include "ultrasonic.h"

int main(void)
{
	init_ports();
	power_on();
	/************************************************************************
	* Ejemplo: uso PWM
	************************************************************************/
//	init_timer1();
//	example_motors();
	/************************************************************************
	* Ejemplo: USART
	* Enviar el valor UBRR
	* Ejemplo: fosc = 16 Mhz, U2Xn= 1, BaudRate = 9600, entonces UBRR= 207
	************************************************************************/
	init_usart(207);
	USART_transmit_string("Hola BT...");
	/************************************************************************
	* Ejemplo: uso TIMER0
	************************************************************************/
	init_ext_int0();
	init_timer0();
	example_sonar();
    while (1) 
    {
		
    }
}