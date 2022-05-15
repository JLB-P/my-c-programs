/*
 * motors.c
 *
 * Created: 5/14/2022 7:49:01 PM
 *  Author: jlb
 * Adapted from eXtremeElectronics library
 * Please give credit to www.eXtremeElectronics.co.in if you use
 * it in your projects and find it useful
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "motors.h"

void motors_init()
{
	/* set up pwm for speed control
	*  COM1A1=1 Clear OC1A/OC1B on Compare Match (Set output to low level)
	*  COM1B1=1 Clear OC1A/OC1B on Compare Match when up-counting. Set OC1A/OC1B on Compare Match when downcounting.
	*  WGM10=1 PWM, Phase Correct, 8-bit
	*/
	TCCR1A=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM10); 
	
	/*clk=fcpu/256 (16 Mhz/256= aprox 62 Khz)
	* to operate dc motor nicely
	* CS12=1, clk/256 (From prescaler)
	*/
	TCCR1B=(1<<CS12);

	//Set the corresponding port pin to output
	DDRB|=(1<<PINB1); //OC1A enable for right motor
	DDRB|=(1<<PINB2); //OC1B enable for left motor

	/*Set the direction control PINs to OUT
	* MPU	|	H BRIDGE
	* ------------------
	* PB1	|	ENA -
	* PD0	|	IN1	|--> RIGHT MOTOR
	* PD1	|	IN2 -
	*		|
	* PB2	|	ENB -
	* PD2	|	IN3	|--> LEFT MOTOR
	* PD3	|	IN4 -
	* -------------*/
	DDRD|=0X0F;	//PD0 to PD3 as output
}

/****************************************************************
* Set the rotation of motor A(LEFT) in given direction and speed
* Inputs:
* dir = MOTOR_FORWARD, MOTOR_BACKWARD or MOTOR_STOP 
* speed = any value from 0 to 255
* Example of use:
* MotorA(MOTOR_FORWARD,120);
*****************************************************************/
void motor_right(uint8_t dir,uint8_t speed) 
{
	//Direction
	if(dir == MOTOR_STOP)
	{
		PORTD &=(~(1<<PD0));
		PORTD &=(~(1<<PD1));
	}

	else if(dir == MOTOR_BACKWARD)
	{
		PORTD &=(~(1<<PD0));
		PORTD |=(1<<PD1);
	}
	else if(dir == MOTOR_FORWARD)
	{
		PORTD &=(~(1<<PD1));
		PORTD |=(1<<PD0);
	}

	//Speed
	uint8_t sreg=SREG;//Status Register

	cli();

	OCR1A=(uint8_t)(((float)speed/255.0)*ROBO_SPEED);

	SREG=sreg;
}

/****************************************************************
* Set the rotation of motor B(RIGHT) in given direction and speed
* Inputs:
* dir = MOTOR_FORWARD, MOTOR_BACKWARD or MOTOR_STOP
* speed = any value from 0 to 255
* Example of use:
* MotorB(MOTOR_FORWARD,120);
*****************************************************************/
void motor_left(uint8_t dir,uint8_t speed)
{
	//Direction
	if(dir == MOTOR_STOP)
	{
		PORTD &=(~(1<<PD2));
		PORTD &=(~(1<<PD3));
	}

	else if(dir == MOTOR_FORWARD)
	{
		PORTD &=(~(1<<PD2));
		PORTD |=(1<<PD3);
	}
	else if(dir == MOTOR_BACKWARD)
	{
		PORTD &=(~(1<<PD3));
		PORTD |=(1<<PD2);
	}

	//Speed
	uint8_t sreg=SREG;

	cli();

	OCR1B=(uint8_t)(((float)speed/255.0)*ROBO_SPEED);

	SREG=sreg;
}
