/*
 * usart.c
 *
 * Created: 3/22/2022 6:49:28 PM
 *  Author: josel
 */ 
/******************************************************************************
* Inicializa el USART
* Entrada: valor de UBRR de las tablas de BAUDRATE
*
*******************************************************************************/
#include <avr/interrupt.h>


void init_usart(unsigned int baudrate)
{
	//Escoge modo de reloj: UMSEL=0 asíncrono, UMSEL=1 síncrono
	UCSR0C &= ~(1<<UMSEL00 | 1<<UMSEL01); // bit UMSEL = 0 asíncrono
	
	//En modo asíncrono escoge la velocidad: U2X=0 normal, U2X=1 doble
	UCSR0A = (1<<U2X0); // bit U2X = 1 doble
	
	//Baudrate ejemplo: fosc = 16 Mhz, U2Xn= 1, BaudRate = 9600, entonces UBRR= 207
	//Ver DataSheet pag.153
	UBRR0H = (unsigned char) (baudrate>>8); // Escribe (MSB) en la parte alta del registro
	UBRR0L = (unsigned char) (baudrate); //Escribe (LSB) el valor en la parte baja
	
	//Tamaño de los datos
	UCSR0C = ((1<<UCSZ00) | (1<<UCSZ01)); //Selecciona registro,8 bits para longitud de datos
	
	//Habilitar el transmisor y receptor
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	//Habilita 2 bits de paro
	//UCSRC = (1<<USBS);
	
	sei(); //Activa interrupciones generales
	//Para activar/desactivar las interrupcines, sólo quitar/poner el símbolo de comentarios
	UCSR0B |= (1<<RXCIE0);	//Activa interrupciones de "recepción completada" (RXCIE=1)
	//y "registro de datos vacío" (UDRIE=1)
	
}