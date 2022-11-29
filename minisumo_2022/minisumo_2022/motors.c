/*
 * motors.c
 *
 * Created: 25/11/2022 05:17:30 a. m.
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "motors.h"

// PWM for speed control
void init_timer1()
{
	TCCR1A |= (1<<WGM10);//WGM10=1 PWM, Phase Correct, 8-bit
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1);	//low level on OC1A/OC1B when up-counting
										//high level on OC1A/OC1B on Compare Match when downcounting
	TCCR1B |= (1<<CS12)|(1<<CS10);	//frequency=fcpu/1024 ~ 15Khz (motors operating frequency)
}

//motor right direction&speed control
void motor_right(uint8_t dir,uint8_t speed)
{
	//direction
	if(dir == motor_stop)
	{
		PORTC &= 0 << PC4;
		PORTC &= 0 << PC5;
	}
	else if(dir == motor_backward)
	{
		PORTC &= 0 << PC4;
		PORTC |= 1 << PC5;
	}
	else if(dir == motor_forward)
	{
		PORTC &= 0 << PC5;
		PORTC |= 1 << PC4;
	}

	//Speed
	uint8_t sreg = SREG;//Status Register

	cli();
	OCR1B = (uint8_t)(((float)(speed/255.0)*robo_speed));
	SREG = sreg;
}

//motor left direction&speed control
void motor_left(uint8_t dir,uint8_t speed)
{
	//Direction
	if(dir == motor_stop)
	{
		PORTB &= 0 << PB3;
		PORTB &= 0 << PB4;
	}
	else if(dir == motor_backward)
	{
		PORTB &= 0 << PB3;
		PORTB |= 1 << PB4;
	}
	else if(dir == motor_forward)
	{
		PORTB &= 0 << PB4;
		PORTB |= 1 << PB3;
	}

	//Speed
	uint8_t sreg = SREG;
	
	cli();
	OCR1A = (uint8_t)(((float)(speed/255.0)*robo_speed));
	SREG = sreg;
}
