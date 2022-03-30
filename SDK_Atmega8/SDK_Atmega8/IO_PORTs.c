/*
 * IO_PORTs.c
 *
 * Created: 01/03/2016 07:16:52 p. m.
 *  Author: JLB
 */ 
#include <avr/io.h>

void Init_Ports (void)
{
		// Define puerto B-->salida
	DDRB = 0xff;
	//LCD de prueba a 4 bits
	/*	Atmega8		LCD
		PB0			RS
		PB1			RW
		PB2			E
		PB4			D4
		PB5			D5
		PB6			D6
		PB7			D7
	*/
	
	// conexiones al ds1302
	/*	Atmega8		DS1302
		PB0			RST
		PB1			SCLK
		PB2			I/O
	*/
		//Usa PB1 (OC1A) como salida para el pulso
		
		//LED1 de prueba modo sleep(azul)
	DDRC |= 1 << PC1 | 1 << PC2;
	PORTC |= 1 << PC1; //Inicia LED (Off=H)
		//LED2 de prueba (amarillo)
	PORTC |= 1 << PC2; //Inicia LED (Off=H)
	//LED3 de prueba WATCHDOG (rojo)
	DDRC |= 1 << PC3;
	PORTC |= 1 << PC3; //Inicia LED (Off=H)
	
	// Salidas para interfaz a 2 hilos TWI
	DDRC|=(1<<PINC4)|(1<<PINC5);	// Como salida SDA y SCL
	PORTC|=(1<<PINC4)|(1<<PINC5);	// SDA y SCL con pull up.
	 	
		
		
	
	// Define PIND2<--entrada para INT0
	DDRD &= 0 << PIND2;
	PORTD |= 1 << PIND2; //Activa Rp
	
	// Configura PIND3-->salida para inidcar sistema on
	DDRD |= 1 << PIND3;
	
}