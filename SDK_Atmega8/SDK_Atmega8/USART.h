/*
 * USART.h
 *
 * Created: 25/03/2016 09:40:28 a. m.
 *  Author: JLB
 */ 


#ifndef USART_H_
#define USART_H_


void Init_USART( unsigned int Baudrate );
unsigned char USART_receive( void );
void USART_transmit( uint8_t data );
void USART_transmit_string( char s[] );

#endif /* USART_H_ */