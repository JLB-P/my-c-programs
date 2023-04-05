/*
 * usart.c
 *
 * Created: 30/11/2021 09:55:24 a. m.
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart.h"

//Global variables
volatile char USART_received_char;

/************************************************************************
	Rutina de atención a las interrupciones del USART
*************************************************************************/
ISR (USART_RX_vect)
{
	USART_received_char=UDR0;
	//UDR =USART_received_char;
	USART_transmit(0x41); //Transmite una "A" y luego el caracter tecleado
	USART_transmit(USART_received_char);
}

/************************************************************************
	Lee el byte que llega por el receptor
*************************************************************************/
unsigned char USART_receive( void )
{
  while ((UCSR0A & 0x80) == 0x00); // Espera por un dato (RXC=1)
  return UDR0;
}

/************************************************************************
	Transmite el dato que se pasa como argumento
*************************************************************************/
void USART_transmit( uint8_t data )
{
  while ((UCSR0A & 0x20) == 0x00);  // Espera hasta que el buffer del transmisor está vacío (UDRE=1)
  UDR0 = data; // Cuando el buffer está vacío, coloca el dato en el registro UDR
}

/************************************************************************
	Transmite una cadena de caracteres
*************************************************************************/
void USART_transmit_string( char s[] )
{	
	int i = 0;
  while (i < 64)
  {
	  if (s[i] == '\0') break;
	  USART_transmit(s[i++]);
  }
}
/******************************************************************************
* Inicializa el USART
* Entrada: valor de UBRR de las tablas de BAUDRATE
*******************************************************************************/
void init_usart(unsigned int baudrate)
{
	//Escoge modo de reloj: UMSEL00 & UMSEL01 =0 asíncrono, UMSEL00=1 síncrono
	UCSR0C &= (~(1<<UMSEL00) & ~(1<<UMSEL00));
	
	//En modo asíncrono escoge la velocidad: U2X=0 normal, U2X=1 doble
	UCSR0A = (1 << U2X0); // bit U2X = 1 doble
	
	//Baudrate ejemplo: fosc = 16 Mhz, U2Xn= 1, BaudRate = 9600, entonces UBRR= 207 (pag.199)
	UBRR0H = (unsigned char) (baudrate>>8); // Escribe (MSB) en la parte alta del registro
	UBRR0L = (unsigned char) (baudrate); //Escribe (LSB) el valor en la parte baja
	
	//Tamaño de los datos
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01); //Selecciona registro,8 bits para longitud de datos
	
	//Habilitar el transmisor y receptor
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
		
	//Habilita 2 bits de paro
	//UCSR0C = (1<<USBS0);
	
	sei(); //Activa interrupciones generales
	//Para activar/desactivar las interrupcines, sólo quitar/poner el símbolo de comentarios
	UCSR0B |= (1<<RXCIE0);	//Activa interrupciones de "recepción completada" (RXCIE0=1)
							//y "registro de datos vacío" (UDRIE0=1)
}