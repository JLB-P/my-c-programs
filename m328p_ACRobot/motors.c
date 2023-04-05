/*
 * motors.c
 *
 * Created: 25/11/2021 05:17:30 a. m.
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "motors.h"

/****************************************************************
* Activa señal pwm para el control de velocidad
*****************************************************************/
void init_timer1()
{
	TCCR1A |= (1<<WGM10);//WGM10=1 PWM, Phase Correct, 8-bit (pag.141 tabla 16.4)
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1);	//Envía nivel bajo por OC1A/OC1B(Pag.141 tabla 16.3)
										//when up-counting. Envía nivel alto por OC1A/OC1B on Compare
										//Match when downcounting(figura 16-8 pág.135)
	TCCR1B |= (1<<CS12)|(1<<CS10);	//frecuencia=fcpu/1024 ~ 15Khz (frecuencia para los motores)
									//tabla 16.5, pag.143
}

/****************************************************************
* Establece rotación de motor DERECHO en una dirección y velocidad
* Inputs:
* dir = MOTOR_FORWARD, MOTOR_BACKWARD or MOTOR_STOP
* speed = cualquier valor de 0 a 255
* Ejemplo:
* MotorA(MOTOR_FORWARD,120);
*****************************************************************/
void motor_right(uint8_t dir,uint8_t speed)
{
	//Dirección
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

	//Velocidad
	uint8_t sreg = SREG;//Status Register

	//cli();

	OCR1A = 13 + speed;//(uint8_t)(((float)(speed/240.0)*ROBO_SPEED));
	SREG = sreg;
}

/****************************************************************
* Establece rotación de motor IZQUIERDO en una dirección y velocidad
* Inputs:
* dir = MOTOR_FORWARD, MOTOR_BACKWARD or MOTOR_STOP
* speed = cualquier valor de 0 a 255
* Ejemplo:
* MotorA(MOTOR_FORWARD,120);
*****************************************************************/
void motor_left(uint8_t dir,uint8_t speed)
{
	//Dirección
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

	//Velocidad
	uint8_t sreg = SREG;

	//cli();

	OCR1B = 16 + speed;//(uint8_t)(((float)speed/240.0)*ROBO_SPEED));

	SREG = sreg;
}

void example_motors()
{
	motor_left(motor_forward,20);
	motor_right(motor_forward,100);
}