/*
 * int0.c
 *
 * Created: 7/29/2021 3:24:05 PM
 *  Author: JOSELUISBARBOSAPACHE
 */ 

#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd_i2c.h"

ISR(INT0_vect)
{
	lcd_i2c_col_row(3,2);
	lcd_i2c_write_string("recibe INT0 ");
	_delay_ms(100);
	lcd_i2c_clr();
}
void init_INT0(void)
{
	EICRA |= 1 << ISC01; //Define sensado de interrupcion en el flanco de bajada (ver tabla 13-2 pag.80)
	EIMSK |= 1 << INT0; //Activa interrupción 0
	sei(); //Habilita interrupciones generales (sei())
}