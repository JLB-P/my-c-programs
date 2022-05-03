/*
 * usart.c
 *
 * Created: 3/22/2022 6:49:28 PM
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart.h"

//Global variables
volatile char usart_received_char;

/*
* Rutina de atención a las interrupciones del USART
*/
ISR (USART_RX_vect)
{
	usart_received_char=UDR0;
	usart_transmit(0x40); //Transmite una "A" y luego el caracter tecleado
	usart_transmit(usart_received_char);
}

/*
* Lee el byte que llega por el receptor
*/
unsigned char usart_receive( void )
{
  while ((UCSR0A & 0x80) == 0x00); // Espera por un dato (RXC=1)
  return UDR0;
}

/*
* Transmite el dato que se pasa como argumento
*/
void usart_transmit( uint8_t data )
{
  while ((UCSR0A & 0x20) == 0x00);  // Espera hasta que el buffer del transmisor está vacío (UDRE=1)
  UDR0 = data; // Cuando el buffer está vacío, coloca el dato en el registro UDR
}

/*
	Transmite una cadena de caracteres
*/
void usart_transmit_string( char s[] )
{	
	int i = 0;
  while (i < 64)
  {
	  if (s[i] == '\0') break;
	  usart_transmit(s[i++]);
  }
}

/*
* Inicializa USART
* Entrada: valor de UBRR de las tablas(datasheet)de BAUDRATE
*/
void init_usart(unsigned int baudrate)
{
	//Escoge modo de reloj: UMSEL=0 asíncrono, UMSEL=1 síncrono
	UCSR0C &= (~(1<<UMSEL00) & ~(1<<UMSEL01)); // bit UMSEL = 0 asíncrono
	
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