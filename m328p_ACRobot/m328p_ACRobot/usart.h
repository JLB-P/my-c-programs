/*
 * usart.h
 *
 * Created: 30/11/2021 09:55:40 a. m.
 *  Author: jlb
 */ 


#ifndef USART_H_
#define USART_H_
void init_usart( unsigned int Baudrate );
unsigned char USART_receive( void );
void USART_transmit( uint8_t data );
void USART_transmit_string( char s[] );

#endif /* USART_H_ */