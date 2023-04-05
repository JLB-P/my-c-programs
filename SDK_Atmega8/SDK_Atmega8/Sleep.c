/*
 * Sleep.c
 *
 * Created: 31/03/2016 08:05:01 p. m.
 *  Author: JLB
 */ 
#include <avr/io.h>
#include <avr/sleep.h> //Agregar esta librería
#include <avr/interrupt.h>
#include <util/delay.h>

int Sleep_example(void)
{
	//Usar PC1 para observar cuando está dormido (inicializa el PC1 en IO_PORTs.c)
	//Usar PC2 para observar cuando lo despiertan (inicializa el PC2 en IO_PORTs.c)
	//Usar el PD2 interrupción para despertarlo (inicializa el PD2 en IO_PORTs.c)
	
	// Define nivel para interrupción INT0 (nivel bajo)
	MCUCR &= ~((1 << ISC01) | (1 << ISC00));

	//while (1)
	//{
		
		PORTC ^= (1 << PC1); //Enciende LED azul
		_delay_ms(500);

		// habilita interrupción
		GICR |= (1 << INT0);

		// define modo
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);

		// habilita sleep
		sleep_enable();
		sei();
		sleep_cpu();
		sleep_disable();
		
		// waking up...
		// disable external interrupt here, in case the external low pulse is too long
		GICR &= ~(1 << INT0);

		// disable all interrupts
		cli();
	//}
}
 
ISR(INT0_vect)
{
	// ISR might be empty, but is necessary nonetheless
	for(int i=0;i<=10;i++)
	{
		PORTC ^= (1 << PC2);    // debugging
		_delay_ms(50);
	}
	PORTC |= 1 << PC2; // apaga LED	
}