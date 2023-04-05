/*
 * leds.c
 *
 * Created: 5/14/2022 11:12:39 PM
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <util/delay.h>

/*Sensor & LED assignment
	MPU		LEDs	SENSORS
	-----------------------
	PD4		LED1	sensor1
	PD5		LED2	sensor2
	PD6		LED3	sensor3
	PD7		LED4	sensor4
	PB0		LED5	sensor5
	PB3		LED6	sensor6
*/
void led_init()
{
	//Make i/o pins as outputs
	DDRD |= (1<<PIND4) | (1<<PIND5) | (1<<PIND6) | (1<<PIND7);
	DDRB |= (1<<PINB0)|(1<<PINB3);
	
	//Make them high to turn off led.
	//LEDs are anode activated
	PORTD |= (1<<PIND4) | (1<<PIND5) | (1<<PIND6) | (1<<PIND7);
	PORTB |= (1<<PINB0)|(1<<PINB3);
}
void test_leds()
{
	int i;
	for(i=0; i<3; i++)
	{
		PORTD &=~(1<<PIND4); //On
		_delay_ms(100);
		PORTD |= (1<<PIND4);//Off
	
		PORTD &=~(1<<PIND5); //On
		_delay_ms(100);
		PORTD |= (1<<PIND5);//Off
	
		PORTD &=~(1<<PIND6); //On
		_delay_ms(100);
		PORTD |= (1<<PIND6);//Off
	
		PORTD &=~(1<<PIND7); //On
		_delay_ms(100);
		PORTD |= (1<<PIND7);//Off
	
		PORTB &=~(1<<PINB0); //On
		_delay_ms(100);
		PORTB |= (1<<PINB0);//Off

		PORTB &=~(1<<PINB3); //On
		_delay_ms(100);
		PORTB |= (1<<PINB3);//Off
	}
}

void ledon(uint8_t id)
{
		if (id<=4){
			PORTD |= (1<<(id+3));
		}
		else if (id == 5){
			PORTB |= (1<<PINB0);
		}
		else if (id == 6){
			PORTB |= (1<<PINB3);
		}
}

void ledoff(uint8_t id)
{
	if (id<=4){
		PORTD &= ~(1<<(id+3));
	}
	if (id == 5){
			PORTB &= ~(1<<PINB0);
	}
    if (id == 6){
			PORTB &= ~(1<<PINB3);
		}
}