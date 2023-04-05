/*
 * USART.c
 *
 * Created: 25/03/2016 09:40:11 a. m.
 *  Author: JLB
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART.h"

//Global variables
volatile char USART_received_char;

/************************************************************************
	Rutina de atención a las interrupciones del USART
*************************************************************************/

ISR (USART_RXC_vect)
{
	USART_received_char=UDR;
	//UDR =USART_received_char;
	USART_transmit(0x41); //Transmite una "A" y luego el caracter tecleado
	USART_transmit(USART_received_char);
}


/************************************************************************
	Lee el byte que llega por el receptor
*************************************************************************/
unsigned char USART_receive( void )
{
  while ((UCSRA & 0x80) == 0x00); // Espera por un dato (RXC=1)
  return UDR;
}

/************************************************************************
	Transmite el dato que se pasa como argumento
*************************************************************************/
void USART_transmit( uint8_t data )
{
  while ((UCSRA & 0x20) == 0x00);  // Espera hasta que el buffer del transmisor está vacío (UDRE=1)
  UDR = data; // Cuando el buffer está vacío, coloca el dato en el registro UDR
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
*
*******************************************************************************/
void Init_USART(unsigned int baudrate)
{
	//Escoge modo de reloj: UMSEL=0 asíncrono, UMSEL=1 síncrono
	UCSRC &= ~(1<<UMSEL); // bit UMSEL = 0 asíncrono
	
	//En modo asíncrono escoge la velocidad: U2X=0 normal, U2X=1 doble
	UCSRA = (1<<U2X); // bit U2X = 1 doble
	
	//Baudrate ejemplo: fosc = 1 Mhz, U2Xn= 1, BaudRate = 9600, entonces UBRR= 12
	//Ver DataSheet pag.153
	UBRRH &= ~(1<<URSEL); // URSEL = 0 para escribir en UBRRH
	UBRRH = (unsigned char) (baudrate>>8); // Escribe (MSB) en la parte alta del registro
	UBRRL = (unsigned char) (baudrate); //Escribe (LSB) el valor en la parte baja
	
	//Tamaño de los datos
	UCSRC = (1<<URSEL)|(1<<UCSZ0) | (1<<UCSZ1); //Selecciona registro,8 bits para longitud de datos
	
	//Habilitar el transmisor y receptor
	UCSRB = (1<<RXEN) | (1<<TXEN);
		
	//Habilita 2 bits de paro
	//UCSRC = (1<<USBS);
	
	sei(); //Activa interrupciones generales
	//Para activar/desactivar las interrupcines, sólo quitar/poner el símbolo de comentarios
	UCSRB |= (1<<RXCIE);	//Activa interrupciones de "recepción completada" (RXCIE=1)
							//y "registro de datos vacío" (UDRIE=1)
	
}