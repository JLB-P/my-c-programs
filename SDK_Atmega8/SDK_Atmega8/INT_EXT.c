/*
 * INT_EXT.c
 *
 * Created: 15/03/2016 07:07:39 a. m.
 *  Author: JLB
 */ 
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_4BIT.h"
#include "Timers.h"
/*
ISR(INT0_vect)
{
	//Timer1_NormalMode_xxx();
	//lcd_col_row(1,2);
	//lcd_write_string("Recibo INT0");
	//_delay_ms(1000);
	//lcd_col_row(1,2);
	//lcd_write_string("           ");
}
*/
void Init_INT_EXT(void)
{
	MCUCR |= 1 << ISC01; //Defino nivel alto a bajo
	GICR |= 1 << INT0; //Activa interrupción 0
	sei(); //Habilita interrupciones generales (sei())
}
