/*
 * comp.c
 *
 * Created: 7/29/2021 4:00:15 PM
 *  Author: JOSELUISBARBOSAPACHE
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd_i2c.h"

ISR(ANALOG_COMP_vect)
{
	while ((ACSR & (1<<ACO)) !=0) //ACO=1 cuando la AIN0 > AIN1(voltaje de referencia)
	//Realiza esta operación mientras voltaje de entrada > voltaje de referencia
	{
		lcd_i2c_col_row(1,2);
		lcd_i2c_write_string("Comparando...");
		_delay_ms(200);
	}
	lcd_i2c_col_row(1,2);
	lcd_i2c_write_string("             ");
}

void init_comp(void)
{
	ACSR |= 1 << ACI | 1 << ACIS1 | 1<< ACIS0;	//Bandera de interrupciones (ACI=1)
												//Modo de interrupción (ACIS1=1:ACIS0=1 flanco de subida) pag.245
	ACSR |= 1 <<ACIE;	//Limpiar bandera de interrupciones (ACSR-->ACI)
	sei();//Habilitar interrupciones generales
}